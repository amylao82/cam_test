
#ifndef __IFRAME_QUEUE_H__
#define __IFRAME_QUEUE_H__

#include <cstdint>
#include <memory>

#include "IFrameBuffer.h"

class IFrameQueue
{
public:
    virtual ~IFrameQueue() {};
    
    virtual void push(const std::shared_ptr<IFrameBuffer>& buffer) = 0;
    virtual std::shared_ptr<IFrameBuffer> pop(std::uint32_t wait = 0) = 0;
    
    virtual void clear() = 0;
    virtual std::uint32_t size() = 0;
    virtual bool empty() = 0;
    virtual bool full() = 0;
    
    static std::shared_ptr<IFrameQueue> create(std::uint32_t maxSize = 4);
};
#endif

