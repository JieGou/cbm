/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrDrawState_DEFINED
#define GrDrawState_DEFINED

#include "GrRODrawState.h"

#include "GrBlend.h"
#include "effects/GrSimpleTextureEffect.h"

/**
 * Modifiable subclass derived from GrRODrawState. The majority of the data that represents a draw
 * state is stored in the parent class. GrDrawState contains methods for setting, adding to, etc.
 * various data members of the draw state. This class is used to configure the state used when
 * issuing draws via GrDrawTarget.
 */
class GrDrawState : public GrRODrawState {
public:
    SK_DECLARE_INST_COUNT(GrDrawState)

    GrDrawState() {
        SkDEBUGCODE(fBlockEffectRemovalCnt = 0;)
        this->reset();
    }

    GrDrawState(const SkMatrix& initialViewMatrix) {
        SkDEBUGCODE(fBlockEffectRemovalCnt = 0;)
        this->reset(initialViewMatrix);
    }

    /**
     * Copies another draw state.
     **/
    GrDrawState(const GrDrawState& state) : INHERITED() {
        SkDEBUGCODE(fBlockEffectRemovalCnt = 0;)
        *this = state;
    }

    /**
     * Copies another draw state with a preconcat to the view matrix.
     **/
    GrDrawState(const GrDrawState& state, const SkMatrix& preConcatMatrix);

    virtual ~GrDrawState() { SkASSERT(0 == fBlockEffectRemovalCnt); }

    /**
     * Resets to the default state. GrEffects will be removed from all stages.
     */
    void reset() { this->onReset(NULL); }

    void reset(const SkMatrix& initialViewMatrix) { this->onReset(&initialViewMatrix); }

    /**
     * Initializes the GrDrawState based on a GrPaint, view matrix and render target. Note that
     * GrDrawState encompasses more than GrPaint. Aspects of GrDrawState that have no GrPaint
     * equivalents are set to default values with the exception of vertex attribute state which
     * is unmodified by this function and clipping which will be enabled.
     */
    void setFromPaint(const GrPaint& , const SkMatrix& viewMatrix, GrRenderTarget*);

    ///////////////////////////////////////////////////////////////////////////
    /// @name Vertex Attributes
    ////

   /**
     * The format of vertices is represented as an array of GrVertexAttribs, with each representing
     * the type of the attribute, its offset, and semantic binding (see GrVertexAttrib in
     * GrTypesPriv.h).
     *
     * The mapping of attributes with kEffect bindings to GrEffect inputs is specified when
     * setEffect is called.
     */

    /**
     *  Sets vertex attributes for next draw. The object driving the templatization
     *  should be a global GrVertexAttrib array that is never changed.
     */
    template <const GrVertexAttrib A[]> void setVertexAttribs(int count) {
        this->setVertexAttribs(A, count);
    }

    /**
     *  Sets default vertex attributes for next draw. The default is a single attribute:
     *  {kVec2f_GrVertexAttribType, 0, kPosition_GrVertexAttribType}
     */
    void setDefaultVertexAttribs();

    /**
     * Helper to save/restore vertex attribs
     */
     class AutoVertexAttribRestore {
     public:
         AutoVertexAttribRestore(GrDrawState* drawState);

         ~AutoVertexAttribRestore() { fDrawState->setVertexAttribs(fVAPtr, fVACount); }

     private:
         GrDrawState*          fDrawState;
         const GrVertexAttrib* fVAPtr;
         int                   fVACount;
     };

    /// @}

    /**
     * Depending on features available in the underlying 3D API and the color blend mode requested
     * it may or may not be possible to correctly blend with fractional pixel coverage generated by
     * the fragment shader.
     *
     * This function considers the current draw state and the draw target's capabilities to
     * determine whether coverage can be handled correctly. This function assumes that the caller
     * intends to specify fractional pixel coverage (via setCoverage(), through a coverage vertex
     * attribute, or a coverage effect) but may not have specified it yet.
     */
    bool couldApplyCoverage(const GrDrawTargetCaps& caps) const;

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Color
    ////

    /**
     *  Sets color for next draw to a premultiplied-alpha color.
     *
     *  @param color    the color to set.
     */
    void setColor(GrColor color) {
        fColor = color;
        this->invalidateBlendOptFlags();
    }

    /**
     *  Sets the color to be used for the next draw to be
     *  (r,g,b,a) = (alpha, alpha, alpha, alpha).
     *
     *  @param alpha The alpha value to set as the color.
     */
    void setAlpha(uint8_t a) { this->setColor((a << 24) | (a << 16) | (a << 8) | a); }

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Coverage
    ////

    /**
     * Sets a constant fractional coverage to be applied to the draw. The
     * initial value (after construction or reset()) is 0xff. The constant
     * coverage is ignored when per-vertex coverage is provided.
     */
    void setCoverage(uint8_t coverage) {
        fCoverage = coverage;
        this->invalidateBlendOptFlags();
    }

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Effect Stages
    /// Each stage hosts a GrEffect. The effect produces an output color or coverage in the fragment
    /// shader. Its inputs are the output from the previous stage as well as some variables
    /// available to it in the fragment and vertex shader (e.g. the vertex position, the dst color,
    /// the fragment position, local coordinates).
    ///
    /// The stages are divided into two sets, color-computing and coverage-computing. The final
    /// color stage produces the final pixel color. The coverage-computing stages function exactly
    /// as the color-computing but the output of the final coverage stage is treated as a fractional
    /// pixel coverage rather than as input to the src/dst color blend step.
    ///
    /// The input color to the first color-stage is either the constant color or interpolated
    /// per-vertex colors. The input to the first coverage stage is either a constant coverage
    /// (usually full-coverage) or interpolated per-vertex coverage.
    ///
    /// See the documentation of kCoverageDrawing_StateBit for information about disabling the
    /// the color / coverage distinction.
    ////

    const GrEffect* addColorEffect(const GrEffect* effect, int attr0 = -1, int attr1 = -1) {
        SkASSERT(NULL != effect);
        SkNEW_APPEND_TO_TARRAY(&fColorStages, GrEffectStage, (effect, attr0, attr1));
        this->invalidateBlendOptFlags();
        return effect;
    }

    const GrEffect* addCoverageEffect(const GrEffect* effect, int attr0 = -1, int attr1 = -1) {
        SkASSERT(NULL != effect);
        SkNEW_APPEND_TO_TARRAY(&fCoverageStages, GrEffectStage, (effect, attr0, attr1));
        this->invalidateBlendOptFlags();
        return effect;
    }

    /**
     * Creates a GrSimpleTextureEffect that uses local coords as texture coordinates.
     */
    void addColorTextureEffect(GrTexture* texture, const SkMatrix& matrix) {
        this->addColorEffect(GrSimpleTextureEffect::Create(texture, matrix))->unref();
    }

    void addCoverageTextureEffect(GrTexture* texture, const SkMatrix& matrix) {
        this->addCoverageEffect(GrSimpleTextureEffect::Create(texture, matrix))->unref();
    }

    void addColorTextureEffect(GrTexture* texture,
                               const SkMatrix& matrix,
                               const GrTextureParams& params) {
        this->addColorEffect(GrSimpleTextureEffect::Create(texture, matrix, params))->unref();
    }

    void addCoverageTextureEffect(GrTexture* texture,
                                  const SkMatrix& matrix,
                                  const GrTextureParams& params) {
        this->addCoverageEffect(GrSimpleTextureEffect::Create(texture, matrix, params))->unref();
    }

    /**
     * When this object is destroyed it will remove any effects from the draw state that were added
     * after its constructor.
     */
    class AutoRestoreEffects : public ::SkNoncopyable {
    public:
        AutoRestoreEffects() : fDrawState(NULL), fColorEffectCnt(0), fCoverageEffectCnt(0) {}

        AutoRestoreEffects(GrDrawState* ds) : fDrawState(NULL), fColorEffectCnt(0), fCoverageEffectCnt(0) {
            this->set(ds);
        }

        ~AutoRestoreEffects() { this->set(NULL); }

        void set(GrDrawState* ds);

        bool isSet() const { return NULL != fDrawState; }

    private:
        GrDrawState* fDrawState;
        int fColorEffectCnt;
        int fCoverageEffectCnt;
    };

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Blending
    ////

    /**
     * Sets the blending function coefficients.
     *
     * The blend function will be:
     *    D' = sat(S*srcCoef + D*dstCoef)
     *
     *   where D is the existing destination color, S is the incoming source
     *   color, and D' is the new destination color that will be written. sat()
     *   is the saturation function.
     *
     * @param srcCoef coefficient applied to the src color.
     * @param dstCoef coefficient applied to the dst color.
     */
    void setBlendFunc(GrBlendCoeff srcCoeff, GrBlendCoeff dstCoeff) {
        fSrcBlend = srcCoeff;
        fDstBlend = dstCoeff;
        this->invalidateBlendOptFlags();
    #ifdef SK_DEBUG
        if (GrBlendCoeffRefsDst(dstCoeff)) {
            GrPrintf("Unexpected dst blend coeff. Won't work correctly with coverage stages.\n");
        }
        if (GrBlendCoeffRefsSrc(srcCoeff)) {
            GrPrintf("Unexpected src blend coeff. Won't work correctly with coverage stages.\n");
        }
    #endif
    }

    /**
     * Sets the blending function constant referenced by the following blending
     * coefficients:
     *      kConstC_GrBlendCoeff
     *      kIConstC_GrBlendCoeff
     *      kConstA_GrBlendCoeff
     *      kIConstA_GrBlendCoeff
     *
     * @param constant the constant to set
     */
    void setBlendConstant(GrColor constant) {
        fBlendConstant = constant;
        this->invalidateBlendOptFlags();
    }

    /**
     * Determines what optimizations can be applied based on the blend. The coefficients may have
     * to be tweaked in order for the optimization to work. srcCoeff and dstCoeff are optional
     * params that receive the tweaked coefficients. Normally the function looks at the current
     * state to see if coverage is enabled. By setting forceCoverage the caller can speculatively
     * determine the blend optimizations that would be used if there was partial pixel coverage.
     *
     * Subclasses of GrDrawTarget that actually draw (as opposed to those that just buffer for
     * playback) must call this function and respect the flags that replace the output color.
     *
     * If the cached BlendOptFlags does not have the invalidate bit set, then getBlendOpts will
     * simply returned the cached flags and coefficients. Otherwise it will calculate the values. 
     */
    BlendOptFlags getBlendOpts(bool forceCoverage = false,
                               GrBlendCoeff* srcCoeff = NULL,
                               GrBlendCoeff* dstCoeff = NULL) const;

    /**
     * We don't use suplied vertex color attributes if our blend mode is EmitCoverage or
     * EmitTransBlack
     */
    bool canIgnoreColorAttribute() const;


    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name View Matrix
    ////

    /**
     * Sets the view matrix to identity and updates any installed effects to compensate for the
     * coord system change.
     */
    bool setIdentityViewMatrix();

    ////////////////////////////////////////////////////////////////////////////

    /**
     * Preconcats the current view matrix and restores the previous view matrix in the destructor.
     * Effect matrices are automatically adjusted to compensate and adjusted back in the destructor.
     */
    class AutoViewMatrixRestore : public ::SkNoncopyable {
    public:
        AutoViewMatrixRestore() : fDrawState(NULL) {}

        AutoViewMatrixRestore(GrDrawState* ds, const SkMatrix& preconcatMatrix) {
            fDrawState = NULL;
            this->set(ds, preconcatMatrix);
        }

        ~AutoViewMatrixRestore() { this->restore(); }

        /**
         * Can be called prior to destructor to restore the original matrix.
         */
        void restore();

        void set(GrDrawState* drawState, const SkMatrix& preconcatMatrix);

        /** Sets the draw state's matrix to identity. This can fail because the current view matrix
            is not invertible. */
        bool setIdentity(GrDrawState* drawState);

    private:
        void doEffectCoordChanges(const SkMatrix& coordChangeMatrix);

        GrDrawState*                                        fDrawState;
        SkMatrix                                            fViewMatrix;
        int                                                 fNumColorStages;
        SkAutoSTArray<8, GrEffectStage::SavedCoordChange>   fSavedCoordChanges;
    };

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Render Target
    ////

    /**
     * Sets the render-target used at the next drawing call
     *
     * @param target  The render target to set.
     */
    void setRenderTarget(GrRenderTarget* target) { fRenderTarget.reset(SkSafeRef(target)); }

    class AutoRenderTargetRestore : public ::SkNoncopyable {
    public:
        AutoRenderTargetRestore() : fDrawState(NULL), fSavedTarget(NULL) {}
        AutoRenderTargetRestore(GrDrawState* ds, GrRenderTarget* newTarget) {
            fDrawState = NULL;
            fSavedTarget = NULL;
            this->set(ds, newTarget);
        }
        ~AutoRenderTargetRestore() { this->restore(); }

        void restore() {
            if (NULL != fDrawState) {
                fDrawState->setRenderTarget(fSavedTarget);
                fDrawState = NULL;
            }
            SkSafeSetNull(fSavedTarget);
        }

        void set(GrDrawState* ds, GrRenderTarget* newTarget) {
            this->restore();

            if (NULL != ds) {
                SkASSERT(NULL == fSavedTarget);
                fSavedTarget = ds->getRenderTarget();
                SkSafeRef(fSavedTarget);
                ds->setRenderTarget(newTarget);
                fDrawState = ds;
            }
        }
    private:
        GrDrawState* fDrawState;
        GrRenderTarget* fSavedTarget;
    };

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Stencil
    ////

    /**
     * Sets the stencil settings to use for the next draw.
     * Changing the clip has the side-effect of possibly zeroing
     * out the client settable stencil bits. So multipass algorithms
     * using stencil should not change the clip between passes.
     * @param settings  the stencil settings to use.
     */
    void setStencil(const GrStencilSettings& settings) {
        fStencilSettings = settings;
        this->invalidateBlendOptFlags();
    }

    /**
     * Shortcut to disable stencil testing and ops.
     */
    void disableStencil() {
        fStencilSettings.setDisabled();
        this->invalidateBlendOptFlags();
    }

    GrStencilSettings* stencil() { return &fStencilSettings; }

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name State Flags
    ////

    void resetStateFlags() {
        fFlagBits = 0;
        this->invalidateBlendOptFlags();
    }

    /**
     * Enable render state settings.
     *
     * @param stateBits bitfield of StateBits specifying the states to enable
     */
    void enableState(uint32_t stateBits) {
        fFlagBits |= stateBits;
        this->invalidateBlendOptFlags();
    }

    /**
     * Disable render state settings.
     *
     * @param stateBits bitfield of StateBits specifying the states to disable
     */
    void disableState(uint32_t stateBits) {
        fFlagBits &= ~(stateBits);
        this->invalidateBlendOptFlags();
    }

    /**
     * Enable or disable stateBits based on a boolean.
     *
     * @param stateBits bitfield of StateBits to enable or disable
     * @param enable    if true enable stateBits, otherwise disable
     */
    void setState(uint32_t stateBits, bool enable) {
        if (enable) {
            this->enableState(stateBits);
        } else {
            this->disableState(stateBits);
        }
    }

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Face Culling
    ////

    /**
     * Controls whether clockwise, counterclockwise, or both faces are drawn.
     * @param face  the face(s) to draw.
     */
    void setDrawFace(DrawFace face) {
        SkASSERT(kInvalid_DrawFace != face);
        fDrawFace = face;
    }

    /// @}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Hints
    /// Hints that when provided can enable optimizations.
    ////

    enum Hints { kVertexColorsAreOpaque_Hint = 0x1, };

    void setHint(Hints hint, bool value) { fHints = value ? (fHints | hint) : (fHints & ~hint); }

    /// @}

    ///////////////////////////////////////////////////////////////////////////

    /** Return type for CombineIfPossible. */
    enum CombinedState {
        /** The GrDrawStates cannot be combined. */
        kIncompatible_CombinedState,
        /** Either draw state can be used in place of the other. */
        kAOrB_CombinedState,
        /** Use the first draw state. */
        kA_CombinedState,
        /** Use the second draw state. */
        kB_CombinedState,
    };

    /** This function determines whether the GrDrawStates used for two draws can be combined into
        a single GrDrawState. This is used to avoid storing redundant GrDrawStates and to determine
        if draws can be batched. The return value indicates whether combining is possible and, if
        so, which of the two inputs should be used. */
    static CombinedState CombineIfPossible(const GrDrawState& a, const GrDrawState& b,
                                           const GrDrawTargetCaps& caps);

    GrDrawState& operator= (const GrDrawState& that);

private:
    void onReset(const SkMatrix* initialViewMatrix);

    /**
     * Determines whether src alpha is guaranteed to be one for all src pixels
     */
    bool srcAlphaWillBeOne() const;

    /**
     * Helper function for getBlendOpts.
     */
    BlendOptFlags calcBlendOpts(bool forceCoverage = false,
                                GrBlendCoeff* srcCoeff = NULL,
                                GrBlendCoeff* dstCoeff = NULL) const;

    void invalidateBlendOptFlags() {
        fBlendOptFlags = kInvalid_BlendOptFlag;
    }

    uint32_t                            fHints;

    // Some of the auto restore objects assume that no effects are removed during their lifetime.
    // This is used to assert that this condition holds.
    SkDEBUGCODE(int fBlockEffectRemovalCnt;)

    /**
     *  Sets vertex attributes for next draw.
     *
     *  @param attribs    the array of vertex attributes to set.
     *  @param count      the number of attributes being set, limited to kMaxVertexAttribCnt.
     */
    void setVertexAttribs(const GrVertexAttrib attribs[], int count);

    typedef GrRODrawState INHERITED;
};

#endif
