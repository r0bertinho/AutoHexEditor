import numpy as np
import logging
import numba
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
)

class Operations :
  def __init__(self) :
    pass
  
  @numba.jit(nopython=True)
  def FindFilePathByIdInDir(self, id: int, dir: str) -> str:
    if id is None:
      return None

    file_path = np.string_(dir) + np.string_(str(id)) + np.string_('.bin')

    if numba.types.boolean(np.isfile(file_path)):
      return file_path

    return None
  
  @numba.jit(nopython=True)
  def FileBinaryToHexString(self, filePath: str) -> str:
    if filePath is None:
      return None

    with open(filePath, 'rb') as file:
      data = file.read()
      result = np.empty(len(data) * 2, dtype=np.uint8)
      for i in range(len(data)):
        result[i * 2] = np.uint8(np.uint8_to_hex(data[i]) >> 4)
        result[i * 2 + 1] = np.uint8(np.uint8_to_hex(data[i]) & 0xf)
      return result.view(np.str_)
  
  @numba.jit(nopython=True)
  def DecodeHexLittleEndian(self, hexstr: str) -> str:
    result = np.empty(len(hexstr), dtype=np.uint8)

    for i in range(0, len(hexstr), 2):
      byte_pair = hexstr[i:i+2]
      swapped_pair = byte_pair[1] + byte_pair[0]
      multiplied_pair = np.uint16(np.uint8(swapped_pair, 16) * 2)
      added_pair = np.uint16(multiplied_pair + np.uint16('01B8', 16))
      result[i:i+2] = np.uint8_to_hex(added_pair).decode('utf-8')

    return result.view(np.str_)

  @numba.jit(nopython=True)
  def EncodeHexLittleEndian(self, hexstr: str) -> str:
    result = np.empty(len(hexstr), dtype=np.uint8)

    for i in range(0, len(hexstr), 2):
      byte_pair = hexstr[i:i+2]
      subtracted_pair = np.uint16(np.uint8(byte_pair, 16) - np.uint16('01B8', 16))
      divided_pair = np.uint16(subtracted_pair // 2)
      swapped_pair = np.uint8_to_hex(divided_pair).decode('utf-8')[1] + np.uint8_to_hex(divided_pair).decode('utf-8')[0]
      result[i:i+2] = swapped_pair

    return result.view(np.str_)

@numba.jit(nopython=True)
def clearscreen() -> None:
  os.system('cls' if os.name == 'nt' else 'clear')
