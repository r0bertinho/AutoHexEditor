from FileOperations import *
from FileMessages import *

@numba.njit
def main() -> None:
  input: str = sys.argv[1]
  
  if input == "help":
    Message.Help()
    
  elif input == "decode":
    Message.Decode()
    
  elif input == "encode":
    Message.Encode()
    

if __name__ == '__main__':
  main()