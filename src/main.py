from FileOperations import *
import logging
import time

logging.basicConfig(
  encoding='UTF-8',
  level=logging.INFO,
  format='%(asctime)s [%(levelname)s]; %(name)r: %(message)s',
  datefmt='%H:%M:%S',
  handlers=[
    logging.FileHandler('logfile.log')
  ]
)

def main() -> None :
  logging.info('App iniciado')
  
  run: bool = True
  while run :
    print("(1: use \"cfg.json\")")
    input: int = int(input("select action : "))
    clearscreen()
  
  logging.info('App fechado')

if __name__ == '__main__' :
  main()