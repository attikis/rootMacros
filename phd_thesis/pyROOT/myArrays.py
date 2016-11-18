#!/usr/bin env python
from array import array

def defineArray(type,size):

     obj = array(type)

     for f in range(0,size):

          obj.append(0)

     return obj
