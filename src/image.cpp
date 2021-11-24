#include "image.h"

namespace Image {
    Texture CreateTexture(const std::vector<uint8_t> *imageData, uint32_t imageWidth, uint32_t imageHeight) {
        GLuint imageTexture;
        glGenTextures(1, &imageTexture);

        glBindTexture(GL_TEXTURE_2D, imageTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData->data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        return {imageTexture, imageWidth, imageHeight};
    }

    Texture CreateTextureFromHmg(const std::vector<uint8_t> &hmgData) {
        auto imageData = new std::vector<uint8_t>();
        uint32_t imageWidth;
        uint32_t imageHeight;

        Hmg::Decode(hmgData, *imageData, imageWidth, imageHeight);

        auto texture = CreateTexture(imageData, imageWidth, imageHeight);

        delete imageData;

        return texture;
    }

    Texture CreateTextureFromPng(const std::vector<uint8_t> &pngData) {
        auto imageData = new std::vector<uint8_t>();
        uint32_t imageWidth;
        uint32_t imageHeight;

        lodepng::decode(*imageData, imageWidth, imageHeight, pngData);

        auto texture = CreateTexture(imageData, imageWidth, imageHeight);

        delete imageData;

        return texture;
    }
}