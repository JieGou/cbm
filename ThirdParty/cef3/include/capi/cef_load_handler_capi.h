// Copyright (c) 2014 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//

#ifndef CEF_INCLUDE_CAPI_CEF_LOAD_HANDLER_CAPI_H_
#define CEF_INCLUDE_CAPI_CEF_LOAD_HANDLER_CAPI_H_
#pragma once

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_frame_capi.h"

#ifdef __cplusplus
extern "C" {
#endif


///
// Implement this structure to handle events related to browser load status. The
// functions of this structure will be called on the browser process UI thread
// or render process main thread (TID_RENDERER).
///
typedef struct _cef_load_handler_t {
  ///
  // Base structure.
  ///
  cef_base_t base;

  ///
  // Called when the loading state has changed. This callback will be executed
  // twice -- once when loading is initiated either programmatically or by user
  // action, and once when loading is terminated due to completion, cancellation
  // of failure.
  ///
  void (CEF_CALLBACK *on_loading_state_change)(struct _cef_load_handler_t* self,
      struct _cef_browser_t* browser, int isLoading, int canGoBack,
      int canGoForward);

  ///
  // Called when the browser begins loading a frame. The |frame| value will
  // never be NULL -- call the is_main() function to check if this frame is the
  // main frame. Multiple frames may be loading at the same time. Sub-frames may
  // start or continue loading after the main frame load has ended. This
  // function may not be called for a particular frame if the load request for
  // that frame fails. For notification of overall browser load status use
  // OnLoadingStateChange instead.
  ///
  void (CEF_CALLBACK *on_load_start)(struct _cef_load_handler_t* self,
      struct _cef_browser_t* browser, struct _cef_frame_t* frame);

  ///
  // Called when the browser is done loading a frame. The |frame| value will
  // never be NULL -- call the is_main() function to check if this frame is the
  // main frame. Multiple frames may be loading at the same time. Sub-frames may
  // start or continue loading after the main frame load has ended. This
  // function will always be called for all frames irrespective of whether the
  // request completes successfully.
  ///
  void (CEF_CALLBACK *on_load_end)(struct _cef_load_handler_t* self,
      struct _cef_browser_t* browser, struct _cef_frame_t* frame,
      int httpStatusCode);

  ///
  // Called when the resource load for a navigation fails or is canceled.
  // |errorCode| is the error code number, |errorText| is the error text and
  // |failedUrl| is the URL that failed to load. See net\base\net_error_list.h
  // for complete descriptions of the error codes.
  ///
  void (CEF_CALLBACK *on_load_error)(struct _cef_load_handler_t* self,
      struct _cef_browser_t* browser, struct _cef_frame_t* frame,
      cef_errorcode_t errorCode, const cef_string_t* errorText,
      const cef_string_t* failedUrl);
} cef_load_handler_t;


#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_CEF_LOAD_HANDLER_CAPI_H_
