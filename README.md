#  FastEMD-Algorithm

## Describtion
This repository is an optimized re-implemenation of the FastEMD-Algorithm ("emd hat ground metric") as desribed by Ofir Pele and Michael Werman [1][1] and [2] [2]. It is written such that it performs at least as fast as Rubner's EMD-Implementation for small arrays while being magnitudes faster using larger arrays. Futhermore, this implementation outperforms the orginal implementation. The Interface is designed such that memory is allocated ones and reused on every call to .calcDistance(). This is specially beneficial when iteration over a sequence of histograms of equal sizes (eq. images). 

This implementation can also be used with openCV.

## Usage
Include "EMDHat.hpp" into your project. Create an EMDHat-instance by calling the initializer with the number of weights / histogram size as input parameter.

You may specify an input number type (all integer types and double) and your preferred interface type (STL (vector or array) or openCV).

To calculate the distance for a given set of weights P and Q, call the .calcDistance() class method.
Example code can be found in the src folder.

## Notes
Calculation of Flow has not been implemented yet. Additionally, this implementation always assumes metric property for the ground distance!

## License
Where not stated differently in the source code, this repository is licensed under the BSD-3 Clause license. See lincense file for details. 

## References
Please cite these papers if you use this code:

[1]: Pele O., Werman M. (2008) A Linear Time Histogram Metric for Improved SIFT Matching. In: Forsyth D., Torr P., Zisserman A. (eds) Computer Vision – ECCV 2008. ECCV 2008. Lecture        Notes in Computer Science, vol 5304. Springer, Berlin, Heidelberg

[2]: O. Pele and M. Werman, "Fast and robust Earth Mover's Distances," 2009 IEEE 12th International Conference on Computer Vision, Kyoto, 2009, pp. 460-467.

The Code of the original implementation can be downloaded at Ofir Pele's [website](http://ofirpele.droppages.com)

