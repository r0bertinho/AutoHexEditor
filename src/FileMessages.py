import numba
import sys
import os

class Message:
  @numba.njit
  def Help() -> int:
    com2: str = sys.argv[2]
    
    if com2 == "encode":
      print(
      """
      """
      )
      return 0
    
    elif com2 == "decode":
      print(
      """
      """
      )
      return 0
    
    elif com2 == "help":
      print(
      """
      Seriously? You need help with help?
      """
      )
      return 0
    
    print(
    """
    -commands: \"help\", \"encode\", \"decode\", \"follow\"
    usage: rahe <command> [args]
    help specific: rahe help <command>
    """
    )
  
  @numba.njit
  def Encode(inlist):
    pass
  
  @numba.njit
  def Decode(inlist):
    pass