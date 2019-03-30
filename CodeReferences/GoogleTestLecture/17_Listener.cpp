// 17_Listener.cpp
#include <iostream>

using namespace std;

/*
Google Test ���� �����ϴ� Listener �� ����ϱ� ���ؼ���
main() �� ���� �ۼ��ؾ� �Ѵ�.
*/

#include "gtest\gtest.h"

class MyPrinter	: public ::testing::EmptyTestEventListener
{
public:
	MyPrinter();
	~MyPrinter();

	void OnTestStart(const ::testing::TestInfo& info)
	{
		cout << "----------------------------------" << endl;
		cout << "name: " << info.name() << endl;
		cout << "test_case_name: " << info.test_case_name() << endl;
	}

	void OnTestPartResult(const ::testing::TestPartResult& result)
	{
		bool fail = result.failed();
		cout << (fail ? "Failed" : "Succeed") << endl;
	}

	void OnTestEnd(const ::testing::TestInfo& info)
	{
		cout << "----------------------------------" << endl;
	}
private:

};

MyPrinter::MyPrinter()
{
}

MyPrinter::~MyPrinter()
{
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::TestEventListeners& listeners
		= ::testing::UnitTest::GetInstance()->listeners();

	listeners.Append(new MyPrinter);

	int ret = RUN_ALL_TESTS();
	system("pause");
	return ret;
}

TEST(SampleTest, foo) 
{ 
	// xml �� �߰����� ������ ����ϰ� �ʹ�.
	// --gtest_output = xml
	RecordProperty("cpu", "1.2");
	RecordProperty("memory", "20");

}
#if 0
// TEST(SampleTest, goo) { SUCCEED(); }
// TEST(SampleTest, hoo) { FAIL(); }
#endif	// #if 0
