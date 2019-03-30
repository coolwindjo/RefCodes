/**
	@file	DECALInspector.cpp
	@date   2018.01.09
	@author	Jo, SeungHyeon (seunghyeon.jo@lge.com)
	@brief
		Implements the DECAL inspector test class source for Extrinsic CALibrtion component.
	@remark
	@warning
		Advanced Driver Assistance Systems Engineering Division
		Copyright (c)  2018~Current LG Electronics Co., LTD., Seoul, Korea
		All rights are reserved.
*/

#include "DECALInspector.h"

DECALInspector::CDECALInspector::CDECALInspector()
	: m_argc(0)
	, m_pargv(NULL)
	, m_nNumFlVal(0)
	, m_nCurrentVal(0)
{
	SetTestArgCount(1);
	SetTestArgString(g_arcPath);

	memset(m_arnCountFn, 0, static_cast<int32_t>(sizeof(uint32_t)*eEND_OF_ENUM_FUNCTIONS));
	memset(&m_stDecalResult, 0, static_cast<int32_t>(sizeof(DecalTopic_t)));
	memset(m_arstFloatValueSet, 0, static_cast<int32_t>(sizeof(DECAL_FloatValueSet_t)*NUM_VALUES));

}


DECALInspector::CDECALInspector::~CDECALInspector()
{
}


// Main functions.
DECALInspector::CDECALInspector* g_poDECALInspector = NULL;
int DECALInspector::CDECALInspector::RunAllTests()
{
	printf("Running Tests\n");
	testing::InitGoogleTest(&m_argc, &m_pargv);
	g_poDECALInspector = this;
	return RUN_ALL_TESTS();
}

void DECALInspector::CDECALInspector::AddValueToCheckValidity(float32_t fValue, float32_t fExpVal, float32_t fHalfRange)
{
	uint8_t bError = 0;
	if (m_nNumFlVal < NUM_VALUES)
	{
		m_arstFloatValueSet[m_nNumFlVal].fValue = fValue;
		m_arstFloatValueSet[m_nNumFlVal].fExpVal = fExpVal;
		m_arstFloatValueSet[m_nNumFlVal++].fHalfRange = fHalfRange;
	}
	else
	{
		if (m_nCurrentVal >= m_nNumFlVal)
		{
			m_nCurrentVal = 0;
		}
		m_arstFloatValueSet[m_nCurrentVal].fValue = fValue;
		m_arstFloatValueSet[m_nCurrentVal].fExpVal = fExpVal;
		m_arstFloatValueSet[m_nCurrentVal++].fHalfRange = fHalfRange;
	}
}

inline void DECALInspector::CDECALInspector::MoveOnNextValueToCheck()
{
	if (m_nCurrentVal >= m_nNumFlVal)
	{
		m_nCurrentVal = 0;
	}
	else
	{
		m_nCurrentVal++;
	}
}

void DECALInspector::CDECALInspector::RemoveAllValues()
{
	memset(m_arstFloatValueSet, 0, static_cast<int32_t>(sizeof(DECAL_FloatValueSet_t)*NUM_VALUES));
	m_nNumFlVal = 0;
}

DECALInspector::CDECALInspector* CFixtureECALgtest::m_poDECALInspector = NULL;

void CFixtureECALgtest::SetUpTestCase()
{
	if (m_poDECALInspector == NULL)
	{
		m_poDECALInspector = g_poDECALInspector;
	}
}
void CFixtureECALgtest::TearDownTestCase()
{
}

TEST_F(CFixtureECALgtest, GetFunctionCount_returnNumsOfExecution)
{
	EXPECT_EQ(static_cast<uint32_t>(1), m_poDECALInspector->GetExeCount(DECALInspector::eINITIALIZE))
		<< "1, eINITIALIZE";
	EXPECT_LE(static_cast<uint32_t>(1), m_poDECALInspector->GetExeCount(DECALInspector::eSTART))
		<< "1+, eSTART";
	EXPECT_LT(static_cast<uint32_t>(0), m_poDECALInspector->GetExeCount(DECALInspector::eEXE_WITH_IMAGE_LEC))
		<< "0+, eEXE_WITH_IMAGE";
	EXPECT_LE(static_cast<uint32_t>(0), m_poDECALInspector->GetExeCount(DECALInspector::eCHANGE_WITH_COMMAND))
		<< "0, eCHANGE_WITH_COMMAND";
	EXPECT_LE(static_cast<uint32_t>(0), m_poDECALInspector->GetExeCount(DECALInspector::eSTOP))
		<< "0+, eSTOP";
	EXPECT_EQ(static_cast<uint32_t>(0), m_poDECALInspector->GetExeCount(DECALInspector::eFINALIZE))
		<< "0, eFINALIZE";
}


TEST_F(CFixtureECALgtest, CompareWithExpectedValues_returnPassOrFailResults)
{
	m_poDECALInspector->ResetToFirstValueToCheck();
	for (int32_t i = 0; i < m_poDECALInspector->GetNumValuesToCheck(); i++)
	{
		EXPECT_NEAR(m_poDECALInspector->GetFValue(), m_poDECALInspector->GetFExpVal(), m_poDECALInspector->GetFHalfRange())
			<< m_poDECALInspector->GetFValue() << " is compared with " << m_poDECALInspector->GetFExpVal();
		m_poDECALInspector->MoveOnNextValueToCheck();
	}
}