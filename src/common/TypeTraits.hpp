/*
 * =====================================================================================
 *
 *       Filename:  TypeTraits.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-19 14:07:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TYPE_TRAITS_HPP

#define TYPE_TRAITS_HPP

#include <cstdint>

#include "Enum.hpp"

namespace my_gl {


     //enum class PrimitiveMode{POINTS,LINES,TRIANGLES,LINE_STRIP,LINE_LOOP,
     //	  TRIANGLE_STRIP,TRIANGLE_FAN};
     const int VERTEX_PER_PRIMITIVE[]={1,2,3,2,2,3,3};
	
     template<DataType=DataType::BYTE>
	  struct DataTypeTraits
	  {
	       typedef void* underlineType;
	       static const int size=-1;
	       static float normalize(underlineType);
	  };

     const int DATA_TYPE_UNDERLINE_SIZE[]={1,1,2,2,4,4};

     template<>
	  struct DataTypeTraits<DataType::BYTE>
	  {
	       typedef int8_t underlineType;
	       static const int size=1;
	       static float normalize(underlineType value)
	       {return value*2+1/255;}
	  };

     template<>
	  struct DataTypeTraits<DataType::UNSIGNED_BYTE>
	  {
	       typedef uint8_t underlineType;
	       static const int size=1;
	       static float normalize(underlineType value)
	       {return value/255;}
	  };

     template<>
	  struct DataTypeTraits<DataType::SHORT>
	  {
	       typedef int16_t underlineType;
	       static const int size=2;
	       static float normalize(underlineType value)
	       {return value*2+1/65536;}
	  };
     template<>
	  struct DataTypeTraits<DataType::UNSIGNED_SHORT>
	  {
	       typedef uint16_t underlineType;
	       static const int size=2;
	       static float normalize(underlineType value)
	       {return value/65536;}
	  };

     template<>
	  struct DataTypeTraits<DataType::FIXED>
	  {
#warning FIXED is not implemented ,this is a dummy
	       typedef uint32_t underlineType;
	       static const int size=4;
	       static float normalize(underlineType value)
	       {return value/65536;}
	  };

     template<>
	  struct DataTypeTraits<DataType::FLOAT>
	  {
	       typedef float underlineType;
	       static const int size=4;
	       static float normalize(underlineType value)

	       {
		    if (value<0)
		    {
			 return 0;
		    }
		    else if (value>1)
		    {
			 return 1;
		    }
		    else
		    {
			 return value;
		    }
	       
	       }
	  };



} /* my_gl */


#endif /* end of include guard: TYPE_TRAITS_HPP */
