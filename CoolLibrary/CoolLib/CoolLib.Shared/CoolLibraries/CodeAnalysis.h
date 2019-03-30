/**
* @file CodeAnalysis.h
* @date 2016-02-08
* @author JO, Seunghyeon (coolwind@hotmail.co.kr)
* @brief Configurations of warnings for Code Analysis
* @remark
* @warning Copyright (c)	2016~Current JO, Seunghyeon Seoul, Korea
*							All rights are reserved.
*/
#pragma once

// no check
#pragma warning(disable: 4819)
//#pragma warning ( disable : 6029 )
//#pragma warning ( disable : 6053 )
//#pragma warning ( disable : 6054 )
//#pragma warning ( disable : 6057 )
#pragma warning ( disable : 6387 )
//#pragma warning ( disable : 6526 )
//#pragma warning ( disable : 6530 )
//#pragma warning ( disable : 6535 )
//#pragma warning(disable: 28182) // .ToString in C++/CLI

// for-loop check
#pragma warning ( default : 6319 )
#pragma warning ( default : 6292 )
#pragma warning ( default : 6293 )
//#pragma warning ( disable : 6294 ) // cv::operations.hpp
//#pragma warning ( disable : 6295 ) // Camera_Config.c
#pragma warning ( default : 6294 ) // cv::operations.hpp
#pragma warning ( default : 6295 ) // Camera_Config.c
#pragma warning ( default : 6296 )
// memory check
#pragma warning ( default : 6308 )
#pragma warning ( default : 6001 )
#pragma warning ( default : 6278 )
#pragma warning ( default : 6279 )
#pragma warning ( default : 6280 )
#pragma warning ( default : 6283 )
// buffer check
#pragma warning ( default : 6053 )
#pragma warning ( default : 6059 )
#pragma warning ( default : 6324 )
#pragma warning ( default : 6202 )
#pragma warning ( default : 6203 )
#pragma warning ( default : 6204 )
#pragma warning ( default : 6200 )
#pragma warning ( disable : 6201 ) // cv::operations.hpp
#pragma warning ( disable : 6385 ) // cv::operations.hpp
#pragma warning ( default : 6386 )
// variable check
#pragma warning ( default : 6244 )
#pragma warning ( default : 6246 )
// bit field check
#pragma warning ( default : 6299 )
// operator check
#pragma warning ( default : 6260 )
#pragma warning ( default : 6334 )
#pragma warning ( default : 6269 )
#pragma warning ( default : 6336 )
// conditional expression check
#pragma warning ( default : 6326 )
#pragma warning ( default : 6259 )
#pragma warning ( default : 6281 )
#pragma warning ( default : 6290 )
#pragma warning ( default : 6291 )
#pragma warning ( default : 6314 )
#pragma warning ( default : 6315 )
#pragma warning ( default : 6316 )
#pragma warning ( default : 6317 )
#pragma warning ( default : 6288 )
#pragma warning ( default : 6289 )
#pragma warning ( default : 6313 )
#pragma warning ( default : 6235 )
#pragma warning ( default : 6236 )
#pragma warning ( default : 6237 )
#pragma warning ( default : 6239 )
#pragma warning ( default : 6240 )
#pragma warning ( default : 6285 )
#pragma warning ( default : 6286 )
#pragma warning ( default : 6282 )
#pragma warning ( default : 6287 )
// casting check
#pragma warning ( default : 6268 )
// pointer check
//#pragma warning ( disable : 6011 ) // cv::mat.hpp
#pragma warning ( default : 6011 ) // cv::mat.hpp
#pragma warning ( default : 6305 )
// function check
#pragma warning ( default : 6031 )
#pragma warning ( default : 6063 )
#pragma warning ( default : 6064 )
#pragma warning ( default : 6066 )
#pragma warning ( default : 6067 )
#pragma warning ( default : 6270)
#pragma warning ( default : 6271)
#pragma warning ( default : 6272)
#pragma warning ( default : 6273)
#pragma warning ( default : 6274)
#pragma warning ( default : 6328)
