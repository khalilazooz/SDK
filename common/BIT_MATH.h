#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_


#define SET_BIT(REGISTER,BIT_NO) (REGISTER|=(1ULL<<BIT_NO))
#define CLR_BIT(REGISTER,BIT_NO) (REGISTER&=~(1ULL<<BIT_NO))
#define TOG_BIT(REGISTER,BIT_NO) (REGISTER^=(1ULL<<BIT_NO))
#define GET_BIT(REGISTER,BIT_NO) ((REGISTER>>BIT_NO)&1ULL)
#define ASSIGN_BIT(REGISTER,BIT_NO,value) (REGISTER=((REGISTER&(~(1ULL<<BIT_NO)))|(val<<BIT_NO))

#define SET_BYTE(VAR,OFFSET)	(VAR |= (0xFFULL<<OFFSET))
#define CLR_BYTE(VAR,OFFSET)	(VAR &=~ (0xFFULL<<OFFSET))
#define GET_BYTE(VAR,OFFSET)	((VAR>>OFFSET)&0XFFULL)

#endif
