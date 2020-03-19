//
//  OpenCVSTLConversionWrapper.h
//  FastEMD
//
//  Created by Till Hainbach on 19.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef OpenCVSTLConversionWrapper_h
#define OpenCVSTLConversionWrapper_h

///@brief thin layer to convert between openCV and STL-containers whil mantaining same interface.

template<typename _T, typename Interface, int _size>
class ConversionWrapper:
{
private:
    typeselector2d<_T, Interface, _size> _container;
    
public:
    
    // 
    inline auto begin();
    inline auto begin() const;
    inline auto end();
    inline auto end() const
    
    
    
    inline const auto size() const;
    inline auto resize();
    
}

#endif /* OpenCVSTLConversionWrapper_h */
