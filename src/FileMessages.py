import numba
import sys
import os

class Message:
  @numba.njit
  def Help():
    print(
"""
-commands: \"help\", \"encode\", \"decode\", \"follow\"
usage: rahe <command> [args]

Examples:
$ rahe encode "myfile.bin"
$ rahe follow "mycfg.init"
"""
)
  
  @numba.njit
  def Encode():
    pass
  
  @numba.njit
  def Decode():
    pass