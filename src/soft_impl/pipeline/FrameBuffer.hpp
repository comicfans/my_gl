/*
 * =====================================================================================
 *
 *       Filename:  FrameBuffer.hpp
 *
 *    Description:  interface of all FrameBuffer type
 *
 *        Version:  1.0
 *        Created:  2011-11-1 10:20:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef FRAME_BUFFER_H

#define FRAME_BUFFER_H


namespace my_gl {
     class FrameBuffer {
     public:
	  virtual void clear()=0;
     	virtual ~FrameBuffer ();
     
     private:
     	/* data */
     };
	
} /* my_gl */

#endif /* end of include guard: FRAME_BUFFER_H */
