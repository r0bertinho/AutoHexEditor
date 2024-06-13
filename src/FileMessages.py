import numba
import sys
import os

class Message:
  @numba.njit
  def Help(inlist):
    print(
"""
-commands: \"help\", \"encode\", \"decode\", \"follow\"
usage: rahe <command> [args]
help specific: rahe help <command>

"""
)
    if inlist[1] == "encode":
      print(
"""

"""
)
    elif inlist[1] == "decode":
      print(
"""

"""
)
    elif inlist[1] == "help":
      print(
"""
Seriously? You need help with help?

"""
)
  
  @numba.njit
  def Encode(inlist):
    pass
  
  @numba.njit
  def Decode(inlist):
    pass