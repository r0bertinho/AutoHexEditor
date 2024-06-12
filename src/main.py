from FileOperations import *
from FileMessages import *

def main() -> None:
  input: str = sys.argv[1]
  
  if input == "help":
    Message.Help()
    
  elif input == "decode":
    Message.Decode(sys.argv[2])
    
  elif input == "encode":
    Message.Encode(sys.argv[2])
    

if __name__ == '__main__':
  main()