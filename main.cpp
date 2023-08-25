
#include <cstdio>
#include <memory>

#include "globalenv.h"
#include "camera_interface.h"
#include "IFrameQueue.h"
#include "IFrameBuffer.h"

using namespace std;

#define CAM_CHANNEL (0)

int main()
{

    //1. init env.
    global_env::env_init();

    //2. create camera device.
    shared_ptr<camera_interface> camera = camera_interface::create(camera_interface::SENSOR_IMX258_1);

    if( 0 != camera->start())
    {
	printf("camera start error!");
    }

    printf("camera start ok!");

    //3. create framequeue.
    shared_ptr<IFrameQueue> frame_queue = IFrameQueue::create();
    camera->addOutputQueue(CAM_CHANNEL, frame_queue);

    //4. enable channel.
    uint32_t ret;
    ret = camera->enableChannel(CAM_CHANNEL, true);

    if(ret != camera_interface::SUCCESS)
    {
	global_env::env_uninit();
	return 0;
    }


    //5. start receive frame...
    std::shared_ptr<IFrameBuffer> frame;
    for(int frame_cnt = 0; frame_cnt < 100; ++frame_cnt)
    {
	frame = frame_queue->pop(100);
	if(frame == nullptr)
	{
	    //receive frame timeout.
	    printf("receive frame timeout\n");
	}
	else
	{
	    //do something...
	    printf("receive frame ok frameidx = %d\n", frame_cnt);
	}
    }

    //7. stop device.
    camera->enableChannel(CAM_CHANNEL, false);
    camera->stop();

    camera.reset();

    //8. free env.
    global_env::env_uninit();

    return 1;
}
