/*!
	@file	DECALInspector.h
	@date   2018.01.09
	@author	Jo, SeungHyeon (seunghyeon.jo@lge.com)
	@brief
		Declares the DECAL inspector test class header for Dynamic Extrinsic CALibrtion component.
	@remark
	@warning
		Advanced Driver Assistance Systems Engineering Division
		Copyright (c)  2018~Current LG Electronics Co., LTD., Seoul, Korea
		All rights are reserved.
*/

#ifndef EXTRINSIC_CALIBRATION_GTEST_H_
#define EXTRINSIC_CALIBRATION_GTEST_H_

#include <time.h>
#include "gtest/gtest.h"

// For testing with Dynamic Extrinsic Calibration result.
#include "topic/DecalTopic.h"
#include "component/decal/DECALInspect.h"

namespace DECALInspector
{

	static char_t* g_arcPath = "D:\\GitRepository\\MyEngine\\TestDrivenDevelopment\\unittest_adas_mpc55_release\\x64\\Debug_SingleThread\\adas.exe";
	static int64_t PIVOT_TIME = 1;
	static const int32_t NUM_VALUES = 128;

	typedef enum
	{
		eCONSTRUCTOR = 0,
		eDESTRUCTOR,
		eINITIALIZE,
		eSTART,
		eSTOP,
		eFINALIZE,
		eEXE_WITH_MOTION,
		eEXE_WITH_QOS,
		eEXE_WITH_IMAGE_LEC,
		eEXE_WITH_IMAGE_OFC,
		eEXE_WITH_IMAGE_EME,
		eCHANGE_WITH_COMMAND,
		eEND_OF_ENUM_FUNCTIONS

	} DECAL_Method_e;

	typedef struct
	{
		float32_t fValue;
		float32_t fExpVal;
		float32_t fHalfRange;
	} DECAL_FloatValueSet_t;

	class CDECALInspector
	{
	public:
		explicit CDECALInspector();
		virtual ~CDECALInspector();
		int32_t RunAllTests();
		void SetTestArgCount(int nArgc) { m_argc = nArgc; }
		void SetTestArgString(char_t* szArgv) { m_pargv = szArgv; }

		// Count up the number of specified function execution.
		inline int32_t CountExecution(DECAL_Method_e nExeNo) { return ++m_arnCountFn[nExeNo]; }
		inline int32_t GetExeCount(DECAL_Method_e nExeNo) { return m_arnCountFn[nExeNo]; }

		// Check the validity of values
		void AddValueToCheckValidity(float32_t fValue, float32_t fExpVal,
										float32_t fHalfRange);
		inline int32_t GetNumValuesToCheck() { return m_nNumFlVal; }
		inline void ResetToFirstValueToCheck() { m_nCurrentVal = 0; }
		inline void MoveOnNextValueToCheck();
		inline float32_t GetFValue() { return m_arstFloatValueSet[m_nCurrentVal].fValue; }
		inline float32_t GetFExpVal() { return m_arstFloatValueSet[m_nCurrentVal].fExpVal; }
		inline float32_t GetFHalfRange() { return m_arstFloatValueSet[m_nCurrentVal].fHalfRange; }
		void RemoveAllValues();


		DecalTopic_t m_stDecalResult;

	private:
		// Count up the number of specified function execution.
		uint32_t m_arnCountFn[eEND_OF_ENUM_FUNCTIONS];

		// Check the validity of values
		DECAL_FloatValueSet_t m_arstFloatValueSet[NUM_VALUES];
		int32_t m_nNumFlVal;
		int32_t m_nCurrentVal;

		int32_t m_argc;
		char_t* m_pargv;
	};

}	// namespace DECALInspector

class CFixtureECALgtest : public ::testing::Test
{
public:
	explicit CFixtureECALgtest() {}

protected:
	/// Suite Fixture.
	static void SetUpTestCase();
	static void TearDownTestCase();
	virtual void SetUp()
	{
		m_lStartTime = time(0);
		m_nPivotTime = DECALInspector::PIVOT_TIME;
	}
	virtual void TearDown()
	{
		time_t endTime = time(0);
		time_t duration = endTime - m_lStartTime;

		EXPECT_TRUE(duration < m_nPivotTime) << "Time exceeded : " << duration;
	}

	static DECALInspector::CDECALInspector* m_poDECALInspector;
	time_t m_lStartTime;
	int64_t m_nPivotTime;

};

#endif // #ifndef EXTRINSIC_CALIBRATION_GTEST_H_