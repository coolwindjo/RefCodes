/**
 Structure description
*/
typedef struct OD_Struct_t
{    
    int16_t   s16bar;    /**< variable description. unit:meter range:10~20*/
	float32_t f32foo;    /**< foo description. unit:radian range:-2pi~+20pi */
	int32_t   s32test;   /**< test description. */
} OD_Struct_t;


/**
 test struct
*/
typedef struct OD_Test_t
{
	int32_t s32foo;    /**< foo unit:ea */
	int32_t s32bar;    /**< bar range:0~120*/
} OD_Test_t;