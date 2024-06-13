#ifdef TAV_HPP
#define TAV_HPP

#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <vector>

// Namespace para operações relacionadas a arquivos e strings hexadecimais
namespace Operations {

  // Estrutura de dados ByteVector, um vector de uint8_t
  using ByteVector = std::vector<uint8_t>;

  // Função fileBinaryToHexString: Converte um arquivo binário em uma string hexadecimal
  void fileBinaryToHexString(const std::string& filePath, const char* tempFileName = "temp.tmp") {
    // Verifica se o caminho do arquivo está vazio
    if (filePath.empty()) {
      throw std::invalid_argument("File path is empty");
    }

    // Converte o caminho do arquivo em um objeto path
    std::filesystem::path file_path(filePath);

    // Verifica se o arquivo existe e se é um arquivo regular
    if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
      throw std::runtime_error("File does not exist or is not a regular file");
    }

    // Abre o arquivo em modo binário para leitura
    std::ifstream file(filePath, std::ios::binary);

    // Verifica se o arquivo foi aberto com sucesso
    if (!file) {
      throw std::runtime_error("Failed to open file");
    }

    // Lê o conteúdo do arquivo e armazena em um ByteVector
    ByteVector data = readFile(filePath);

    // Inicializa uma string de resultado com tamanho suficiente para armazenar a string hexadecimal
    char result[data.size() * 2 + 1];
    result[0] = '\0';

    // Converte cada byte do ByteVector em um caractere hexadecimal e armazena na string de resultado
    for (uint8_t byte : data) {
      uint8_t highNibble = byte >> 4;
      uint8_t lowNibble = byte & 0xf;
      char highNibbleChar = highNibble < 10 ? '0' + highNibble : 'A' + highNibble - 10;
      char lowNibbleChar = lowNibble < 10 ? '0' + lowNibble : 'A' + lowNibble - 10;
      std::snprintf(result + strlen(result), 3, "%c%c", highNibbleChar, lowNibbleChar);
    }

    // Cria um arquivo temporário em modo binário para escrita
    std::ofstream tempFile(tempFileName, std::ios::binary);

    // Verifica se o arquivo temporário foi aberto com sucesso
    if (!tempFile) {
      throw std::runtime_error("Failed to open temporary file");
    }

    // Escreve a string hexadecimal no arquivo temporário
    tempFile.write(result, strlen(result));
    tempFile.close();
  }

  // Função readFile: Lê o conteúdo de um arquivo e retorna um ByteVector
  ByteVector readFile(const std::string& filePath) {
    // Abre o arquivo em modo binário para leitura
    std::ifstream file(filePath, std::ios::binary);

    // Verifica se o arquivo foi aberto com sucesso
    if (!file) {
      throw std::runtime_error("Failed to open file");
    }

    // Obtém o tamanho do arquivo
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Inicializa um ByteVector com tamanho suficiente para armazenar o conteúdo do arquivo
    ByteVector data(fileSize);

    // Lê o conteúdo do arquivo no ByteVector
    file.read(reinterpret_cast<char*>(data.data()), fileSize);

    return data;
  }

  // Função isFileEmpty: Verifica se um arquivo está vazio
  bool isFileEmpty(const std::string& filePath) {
    // Abre o arquivo em modo binário para leitura
    std::ifstream file(filePath, std::ios::binary);

    // Verifica se o arquivo foi aberto com sucesso
    if (!file) {
      throw std::runtime_error("Failed to open file");
    }

    // Verifica se o arquivo está vazio
    return file.peek() == std::ifstream::traits_type::eof();
  }

  // Namespace para operações relacionadas a strings hexadecimais
  namespace Hex {

    // Função decodeHexLittleEndian: Decodifica uma string hexadecimal em little-endian
    void decodeHexLittleEndian(const std::string& hexstr, const char* tempFileName = "temp.tmp") {
      // Verifica se a string hexadecimal está vazia
      if (hexstr.empty()) {
        throw std::invalid_argument("Hex string is empty");
      }

      // Inicializa um ByteVector com tamanho suficiente para armazenar a string hexadecimal decodificada
      ByteVector result(hexstr.size() / 2);

      // Decodifica cada par de caracteres hexadecimal em um byte e armazena no ByteVector
      for (size_t i = 0; i < hexstr.size(); i += 2) {
        std::string byte_pair = hexstr.substr(i, 2);
        std::string swapped_pair = byte_pair[1] + byte_pair[0];
        uint16_t multiplied_pair = static_cast<uint16_t>(std::stoul(swapped_pair, 0, 16) * 2);
        uint16_t added_pair = multiplied_pair + 0x01B8;
        uint8_t highByte = (added_pair >> 8) & 0xFF;
        uint8_t lowByte = added_pair & 0xFF;
        result[i / 2] = (highByte << 4) | (lowByte >> 4);
      }

      // Inicializa uma string de resultado com tamanho suficiente para armazenar a string hexadecimal decodificada
      char decoded_str[result.size() * 2 + 1];
      decoded_str[0] = '\0';

      // Converte cada byte do ByteVector em um caractere hexadecimal e armazena na string de resultado
      for (uint8_t byte : result) {
        std::snprintf(decoded_str + strlen(decoded_str), 3, "%02X", byte);
      }

      // Cria um arquivo temporário em modo binário para escrita
      std::ofstream tempFile(tempFileName, std::ios::binary);

      // Verifica se o arquivo temporário foi aberto com sucesso
      if (!tempFile) {
        throw std::runtime_error("Failed to open temporary file");
      }

      // Escreve a string hexadecimal decodificada no arquivo temporário
      tempFile.write(decoded_str, strlen(decoded_str));
      tempFile.close();
    }

    // Função encodeHexLittleEndian: Codifica uma string hexadecimal em little-endian
    void encodeHexLittleEndian(const std::string& hexstr, const char* tempFileName = "temp.tmp") {
      // Verifica se a string hexadecimal está vazia
      if (hexstr.empty()) {
        throw std::invalid_argument("Hex string is empty");
      }

      // Inicializa um ByteVector com tamanho suficiente para armazenar a string hexadecimal codificada
      ByteVector result(hexstr.size() / 2);

      // Codifica cada par de caracteres hexadecimal em um byte e armazena no ByteVector
      for (size_t i = 0; i < hexstr.size(); i += 2) {
        std::string byte_pair = hexstr.substr(i, 2);
        uint16_t subtracted_pair = static_cast<uint16_t>(std::stoul(byte_pair, 0, 16) - 0x01B8);
        uint16_t divided_pair = subtracted_pair / 2;
        uint8_t highByte = (divided_pair >> 8) & 0xFF;
        uint8_t lowByte = divided_pair & 0xFF;
        char swapped_pair[3] = {0};
        std::snprintf(swapped_pair, 3, "%02X", lowByte);
        std::string swapped_str = std::string(1, swapped_pair[0]) + std::string(1, swapped_pair[1]);
        result[i / 2] = static_cast<uint8_t>(std::stoul(swapped_str, 0, 16));
      }

      // Inicializa uma string de resultado com tamanho suficiente para armazenar a string hexadecimal codificadaA string de resultado é criada para armazenar a string hexadecimal codificada.
      char encoded_str[result.size() * 2 + 1];
      encoded_str[0] = '\0';

      // Converte cada byte do ByteVector em um caractere hexadecimal e armazena na string de resultado
      for (uint8_t byte : result) {
        std::snprintf(encoded_str + strlen(encoded_str), 3, "%02X", byte);
      }

      // Cria um arquivo temporário em modo binário para escrita
      std::ofstream tempFile(tempFileName, std::ios::binary);

      // Verifica se o arquivo temporário foi aberto com sucesso
      if (!tempFile) {
        throw std::runtime_error("Failed to open temporary file");
      }

      // Escreve a string hexadecimal codificada no arquivo temporário
      tempFile.write(encoded_str, strlen(encoded_str));
      tempFile.close();
    }

  } // namespace Hex

} // namespace Operations

#endif