
// =====================================================
//
// 数据帧定义文件
// Seevision
//
// =====================================================

#ifndef _IFRAME_BUFFER_H_
#define _IFRAME_BUFFER_H_

#include <cstdint>

class IFrameBuffer
{
public:
    enum PixelFmt
    {
        PIXEL_FMT_UNKNOWN = 0,
        PIXEL_FMT_BAYER_RGGB16,
        PIXEL_FMT_YUYV,
        PIXEL_FMT_NV12,
        PIXEL_FMT_H264,
        PIXEL_FMT_H265,
        PIXEL_FMT_MJPEG,
        PIXEL_FMT_RAW16,
    };
    
    enum PixelExtFmt
    {
        PIXEL_FMT_EXT_UNKNOWN = 0,
        PIXEL_FMT_EXT_I,
        PIXEL_FMT_EXT_P,
        PIXEL_FMT_EXT_B,
    };
    
    virtual ~IFrameBuffer() {}
    
    virtual void setSeq(std::uint32_t seq) = 0;
    virtual std::uint32_t getSeq() = 0;
    virtual void setTimeStamp(std::uint64_t timestamp) = 0;
    virtual std::uint64_t getTimeStamp() = 0;
    
    virtual IFrameBuffer::PixelFmt getPixelFmt() = 0;
    virtual void setPixelExtFmt(const IFrameBuffer::PixelExtFmt& fmt) {}
    virtual IFrameBuffer::PixelExtFmt getPixelExtFmt() = 0;
    virtual std::int32_t getWidth() = 0;
    virtual std::int32_t getHeight() = 0;
    
    virtual char *getVirAddr(std::int32_t idx, std::uint32_t& bufSize) = 0;
    virtual std::uint64_t getPhyAddr(std::int32_t idx) = 0;
    virtual std::uint32_t getDataLen() = 0;
    virtual void setDataLen(std::uint32_t len) = 0;
    virtual void setExtData(void* pBuf,std::uint32_t bufSize) = 0;
    virtual void* getExtData(std::uint32_t &bufSize) = 0;
    
    virtual std::uint32_t writeData(const char *data, std::uint32_t dataLen, std::uint32_t offset = 0) = 0;
    virtual std::uint32_t readData(char *buf, std::uint32_t bufSize, std::uint32_t offset = 0) = 0;
    
};

#endif

