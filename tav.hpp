#ifdef TAV_HPP
#define TAV_HPP

#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <vector>

namespace Operations {
namespace File {

using ByteVector = std::vector<uint8_t>;

void fileBinaryToHexString(const std::string& filePath, const char* tempFileName = "temp.tmp") {
    if (filePath.empty()) {
        throw std::invalid_argument("File path is empty");
    }

    std::filesystem::path file_path(filePath);
    if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
        throw std::runtime_error("File does not exist or is not a regular file");
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    ByteVector data = readFile(filePath);

    char result[data.size() * 2 + 1];
    result[0] = '\0';

    for (uint8_t byte : data) {
        uint8_t highNibble = byte >> 4;
        uint8_t lowNibble = byte & 0xf;
        char highNibbleChar = highNibble < 10 ? '0' + highNibble : 'A' + highNibble - 10;
        char lowNibbleChar = lowNibble < 10 ? '0' + lowNibble : 'A' + lowNibble - 10;
        std::snprintf(result + strlen(result), 3, "%c%c", highNibbleChar, lowNibbleChar);
    }

    std::ofstream tempFile(tempFileName, std::ios::binary);
    if (!tempFile) {
        throw std::runtime_error("Failed to open temporary file");
    }

    tempFile.write(result, strlen(result));
    tempFile.close();
}

ByteVector readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    ByteVector data(fileSize);
    file.read(reinterpret_cast<char*>(data.data()), fileSize);

    return data;
}

bool isFileEmpty(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    return file.peek() == std::ifstream::traits_type::eof();
}

} // namespace File

namespace Hex {

void decodeHexLittleEndian(const std::string& hexstr, const char* tempFileName = "temp.tmp") {
    if (hexstr.empty()) {
        throw std::invalid_argument("Hex string is empty");
    }

    ByteVector result(hexstr.size() / 2);

    for (size_t i = 0; i < hexstr.size(); i += 2) {
        std::string byte_pair = hexstr.substr(i, 2);
        std::string swapped_pair = byte_pair[1] + byte_pair[0];
        uint16_t multiplied_pair = static_cast<uint16_t>(std::stoul(swapped_pair, 0, 16) * 2);
        uint16_t added_pair = multiplied_pair + 0x01B8;
        uint8_t highByte = (added_pair >> 8) & 0xFF;
        uint8_t lowByte = added_pair & 0xFF;
        result[i / 2] = (highByte << 4) | (lowByte >> 4);
    }

    char decoded_str[result.size() * 2 + 1];
    decoded_str[0] = '\0';

    for (uint8_t byte : result) {
        std::snprintf(decoded_str + strlen(decoded_str), 3, "%02X", byte);
    }

    std::ofstream tempFile(tempFileName, std::ios::binary);
    if (!tempFile) {
        throw std::runtime_error("Failed to open temporary file");
    }

    tempFile.write(decoded_str, strlen(decoded_str));
    tempFile.close();
}

void encodeHexLittleEndian(const std::string& hexstr, const char* tempFileName = "temp.tmp") {
    if (hexstr.empty()) {
        throw std::invalid_argument("Hex string is empty");
    }

    ByteVector result(hexstr.size() / 2);

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

    char encoded_str[result.size() * 2 + 1];
    encoded_str[0] = '\0';

    for (uint8_t byte : result) {
        std::snprintf(encoded_str + strlen(encoded_str), 3, "%02X", byte);
    }

    std::ofstream tempFile(tempFileName, std::ios::binary);
    if (!tempFile) {
        throw std::runtime_error("Failed to open temporary file");
    }

    tempFile.write(encoded_str, strlen(encoded_str));
    tempFile.close();
}

} // namespace Hex
} // namespace Operations

#endif