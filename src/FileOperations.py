import logging
import sys
import os

logging.basicConfig(
  encoding='UTF-8',
  level=logging.INFO,
  format='%(asctime)s [%(levelname)s]; %(name)r: %(message)s',
  datefmt='%H:%M:%S',
  handlers=[
    logging.FileHandler('logfile.log'),
    logging.StreamHandler(sys.stdout)
  ]
# Tipos de mensagem de log:
#*  logging.debug('Mensagem de debug')
#?  logging.info('Mensagem de log')
#!  logging.error('Mensagem de erro')
)

class Operations :
  def __init__(self) :
    pass
  
  def FindFilePathByIdInDir(id: int, dir: str) -> str :
    if id == None :
      return None
    
    file_path: str = os.path.join(dir, (str(id) + '.bin'))
    
    if os.path.exists(file_path) :
      return file_path
    
    return None
  
  def FileBinaryToHexString(filePath: str) -> str :
    if filePath == None :
      return None
    
    with open(filePath, 'rb') as file :
      return file.read().hex()

def clearscreen() -> None :
  os.system('cls' if os.name == 'nt' else 'clear')
