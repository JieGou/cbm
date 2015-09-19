#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

#include <fflua.h>

using namespace ff;

class base_t
{
public:
	base_t():v(789){}
	void dump()
	{
		printf("in %s a:%d\n", __FUNCTION__, v);
	}
	int v;
};
class foo_t: public base_t
{
public:
	foo_t(int b):a(b)
	{
		printf("in %s b:%d this=%p\n", __FUNCTION__, b, this);
	}
	~foo_t()
	{
		printf("in %s\n", __FUNCTION__);
	}
	void print(int64_t a, base_t* p) const
	{
		printf("in foo_t::print a:%ld p:%p\n", (long)a, p);
	}

	static void dumy()
	{
		printf("in %s\n", __FUNCTION__);
	}
	int a;
};

//! lua talbe �����Զ�ת��Ϊstl ����
void dumy(map<string, string> ret, vector<int> a, list<string> b, set<int64_t> c)
{
	printf("in %s begin ------------\n", __FUNCTION__);
	for (map<string, string>::iterator it =  ret.begin(); it != ret.end(); ++it)
	{
		printf("map:%s, val:%s:\n", it->first.c_str(), it->second.c_str());
	}
	printf("in %s end ------------\n", __FUNCTION__);
}

class clazz{
public:
	static void static_func(){
		printf("in clazz::%s end ------------\n", __FUNCTION__);
	}
};

static void lua_reg(lua_State* ls)
{
	//! ע����ຯ��, ctor() Ϊ���캯��������
	fflua_register_t<base_t, ctor()>(ls, "base_t")  //! ע�ṹ�캯��
		.def(&base_t::dump, "dump")     //! ע�����ĺ���
		.def(&base_t::v, "v");          //! ע����������

	//! ע�����࣬ctor(int) Ϊ���캯���� foo_tΪ�������ƣ� base_tΪ�̳еĻ�������
	fflua_register_t<foo_t, ctor(int)>(ls, "foo_t", "base_t")
		.def(&foo_t::print, "print")        //! ����ĺ���
		.def(&foo_t::a, "a");               //! ������ֶ�

	fflua_register_t<>(ls)
		.def(&dumy, "dumy");                //! ע�ᾲ̬����


	fflua_register_t<clazz, ctor()>(ls, "clazz")
		.def(&clazz::static_func, "static_func"); 

}

int main(int argc, char* argv[])
{

	fflua_t fflua;
	try 
	{
		//! ע��C++ ����lua��
		fflua.reg(lua_reg);

		//! ����lua�ļ�
		fflua.add_package_path("./");
#ifdef _WIN32
		fflua.load_file("../test.lua");
#else
		fflua.load_file("test.lua");
#endif
		//! ��ȡȫ�ֱ���
		int var = 0;
		assert(0 == fflua.get_global_variable("test_var", var));
		//! ����ȫ�ֱ���
		assert(0 == fflua.set_global_variable("test_var", ++var));

		//! ִ��lua ���
		fflua.run_string("print(\"exe run_string!!\")");

		//! ����lua����, ����������Ϊ����
		int32_t arg1 = 1;
		float   arg2 = 2;
		double  arg3 = 3;
		string  arg4 = "4";
		fflua.call<bool>("test_func", arg1, arg2, arg3,  arg4);

		//! ����lua������stl������Ϊ������ �Զ�ת��Ϊlua talbe
		vector<int> vec;        vec.push_back(100);
		list<float> lt;         lt.push_back((float)99.99);
		set<string> st;         st.insert("OhNIce");
		map<string, int> mp;    mp["key"] = 200;
		fflua.call<string>("test_stl", vec, lt, st,  mp);

		//! ����lua �������� talbe���Զ�ת��Ϊstl�ṹ
		vec = fflua.call<vector<int> >("test_return_stl_vector");
		lt  = fflua.call<list<float> >("test_return_stl_list");
		st  = fflua.call<set<string> >("test_return_stl_set");
		mp  = fflua.call<map<string, int> >("test_return_stl_map");

		//! ����lua������c++ ������Ϊ����, foo_t ���뱻ע���
		foo_t* foo_ptr = new foo_t(456);
		fflua.call<void>("test_object", foo_ptr);

		//! ����lua������c++ ������Ϊ����ֵ, foo_t ���뱻ע��� 
		assert(foo_ptr == fflua.call<foo_t*>("test_ret_object", foo_ptr));
		//! ����lua������c++ ������Ϊ����ֵ, �Զ�ת��Ϊ����
		base_t* base_ptr = fflua.call<base_t*>("test_ret_base_object", foo_ptr);
		assert(base_ptr == foo_ptr);

	}
	catch (exception& e)
	{
		printf("exception:%s\n", e.what());


	}
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
