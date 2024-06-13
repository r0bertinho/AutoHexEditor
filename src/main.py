from FileOperations import *
from FileMessages import *

def main() -> None:
  input: str = sys.argv[1]
  inptlist = []
  
  for i in len(sys.argv):
    if i > 1:
      inptlist.append(sys.argv[i])
  
  if input == "help":
    Message.Help(inptlist)
    
  elif input == "decode":
    Message.Decode(inptlist)
    
  elif input == "encode":
    Message.Encode(inptlist)
    

if __name__ == '__main__':
  main()