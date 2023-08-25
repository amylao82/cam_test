#ifndef __CAMERA_INTERFACE_H__
#define __CAMERA_INTERFACE_H__

#include <cstdint>
#include <atomic>
//#include "FrameBuffer.h"
//#include "FrameQueue.h"

#include "IFrameBuffer.h"
#include "IFrameQueue.h"


class camera_interface
{
public:
    typedef enum {
	SENSOR_IMX258LDC = 0,
	SENSOR_IMX258_1,
	SENSOR_IMX258_2,
	SENSOR_S5K5E9
    } SENSOR_TYPE;

    enum
    {
        ERROR = -1,
        SUCCESS = 0,
        INVALID_PARAME,
        NOT_SUPPORT,
        UNAVAILABLE,
        DEV_BUSY,
    };
    
    enum
    {
        MAX_CHANNELS = 8
    };
    
    enum
    {
        /* 通道号传入GLOBAL_CHANNEL表示对所有通道有效 */
        GLOBAL_CHANNEL = 0xffffffff,
    };
    
    enum
    {
        CAPABILITY_NONE = 0,
        CAPABILITY_SET_FPS = (1LU << 1),
        CAPABILITY_SET_ENCODE_INFO = (1LU << 2),
        CAPABILITY_OSD = (1LU << 3),
        CAPABILITY_ZOOM = (1LU << 4),
        CAPABILITY_PHOTOGRAPH = (1LU << 5),
        CAPABILITY_SET_INPUT_INFO = (1LU << 6),
    };
    
    enum
    {
        OSD_ID_TIME = 0,
        OSD_ID_RECORD,
        OSD_ID_PIC,
        OSD_ID_USER_0,
        OSD_ID_USER_1,
        OSD_ID_MAX,
    };
    
    enum
    {
        OSD_FONT_SIZE_16X16,
        OSD_FONT_SIZE_32X32,
    };
    
    enum EncodeProfile
    {
        ENCODE_PROFILE_MAIN = 0,
        ENCODE_PROFILE_HIGH,
        ENCODE_PROFILE_BASELINE,
    };
    
    enum EncodeFmt
    {
        ENCODE_FMT_UNKNOWN = 0,
        ENCODE_FMT_NV12,
        ENCODE_FMT_H264,
        ENCODE_FMT_H265,
        ENCODE_FMT_MJPEG,
    };
    
    enum EncodeRcMode
    {
        ENCODE_RC_MODE_CBR = 0,
        ENCODE_RC_MODE_VBR,
        ENCODE_RC_MODE_ABR,
        ENCODE_RC_MODE_MAX,
    };

    
    struct Rect
    {
        std::int32_t x;
        std::int32_t y;
        std::int32_t w;
        std::int32_t h;
    };
    
    struct Size
    {
        std::int32_t w;
        std::int32_t h;
    };
    
    struct ChannelInfo
    {
        struct
        {
            std::int32_t w;
            std::int32_t h;
            std::int32_t maxFps;
        }res[8];
        std::uint32_t resNum;
        
        EncodeFmt fmt[8];
        std::uint32_t fmtNum;
    };
    
    struct EncodeInfo
    {
        EncodeProfile profile;
        EncodeFmt fmt;
        EncodeRcMode rcMode;
        /* 单位是kbps */
        std::uint32_t bitRate;
        std::uint32_t gop;
    };
    
    struct PhotoInfo
    {
        /* 连怕多少张 */
        std::uint32_t num;
        /* 连拍间隔 */
        std::uint32_t interval;
        std::int32_t EVStep;
        /* 拍照格式 */
        EncodeInfo encInfo;
        std::int32_t width;
        std::int32_t height;
        /* false 通过拉伸得到目标分辨率
         * true 使用裁剪+拉伸得到目标分辨率，保证图像不变形 */
        bool crop;
        /* 拍原始图像 */
        bool enRaw;
    };
    
    struct ImageColor
    {
        // 范围
        /* 0 - 100*/
        
        std::int32_t brightness;
        std::int32_t saturation;
        std::int32_t contrast;
        std::int32_t sharpness;
        std::int32_t hue;
    };
    
    typedef struct AEExpoValue
    {
        uint32_t u32FNx10;
        uint32_t u32SensorGain;
        uint32_t u32ISPGain;
        uint32_t u32UShutter;
    }AEExpoValue;

    typedef struct AEExpoInfo
    {
        AEExpoValue   stExpoValueLong;
        AEExpoValue   stExpoValueShort;
    } AEExpoInfo;

    typedef struct AEEvComp
    {
        int32_t s32EV;
        uint32_t u32Grad;
    } AEEvComp;

    typedef enum AEMode
    {
        AE_MODE_AUTO,  // auto
        AE_MODE_AV, // aperture priority
        AE_MODE_SV,
        AE_MODE_TV, // shutter priority
        AE_MODE_M,  // manual mode
        AE_MODE_MAX
    } AEMode_e;

    typedef enum AEWinWeightMode
    {
        AE_WEIGHT_AVERAGE = 1,
        AE_WEIGHT_CENTER,
        AE_WEIGHT_SPOT,
        AE_WEIGHT_MAX
    } AEWinWeightMode_e;

    typedef enum AEFlickerType
    {
        AE_FLICKER_TYPE_DISABLE = 0,
        AE_FLICKER_TYPE_60HZ    = 1,
        AE_FLICKER_TYPE_50HZ    = 2,
        AE_FLICKER_TYPE_AUTO    = 3,
        AE_FLICKER_TYPE_MAX
    } AEFlickerType_e;

    typedef struct AWBQueryInfo
    {
        uint16_t u16Rgain;
        uint16_t u16Grgain;
        uint16_t u16Gbgain;
        uint16_t u16Bgain;
        uint16_t u16ColorTemp;
    } AWBQueryInfo;

    typedef enum AWBModeType
    {
        AWB_MODE_AUTO,
        AWB_MODE_INCANDESCENT,
        AWB_MODE_SUNNY,
        AWB_MODE_CLOUDY,
        AWB_MODE_FLUORESCENT,
        AWB_MODE_DIVING,
        AWB_MODE_D4000,
        AWB_MODE_D5000,
        AWB_MODE_D9000,
        AWB_MODE_D10000,
        AWB_MODE_MAX
    } AWBModeType_e;

    typedef enum AWBHueEffect
    {
        AWB_EFFECT_STANDARD,
        AWB_EFFECT_WARM,
        AWB_EFFECT_COOL
    } AWBHueEffect_e;

    typedef struct Coordinates
    {
        uint32_t left;
        uint32_t top;
        uint32_t right;
        uint32_t bottom;
    }Coordinates;

    
    static std::shared_ptr<camera_interface> create(SENSOR_TYPE type);

    virtual ~camera_interface() {}
    
    virtual std::int32_t start() = 0;
    virtual void stop() = 0;
    
    virtual std::uint64_t getCapabilitys() = 0;
    virtual bool isRealStarted() = 0;
	
    virtual void addOutputQueue(std::uint32_t chn, const std::shared_ptr<IFrameQueue>& queue) = 0;
    virtual void delOutputQueue(std::uint32_t chn, const std::shared_ptr<IFrameQueue>& queue) = 0;
    
    virtual std::uint32_t getChannels() = 0;
    virtual std::int32_t getChannelInfo(std::uint32_t chn, camera_interface::ChannelInfo& info) = 0;
    virtual std::int32_t setEncodeInfo(std::uint32_t chn, const EncodeInfo& info) = 0;;
    virtual std::int32_t getEncodeInfo(std::uint32_t chn, EncodeInfo& info) = 0;;
    virtual std::int32_t getResolution(std::uint32_t chn, Size& size) = 0;
    virtual std::int32_t setResolution(std::uint32_t chn, const Size& size) = 0;
    
    virtual std::int32_t getFps(std::uint32_t chn, std::uint32_t& fps) = 0;
    virtual std::int32_t setFps(std::uint32_t chn, std::uint32_t fps) = 0;
    virtual std::int32_t setMirror(std::uint32_t chn, bool b) = 0;
    virtual std::int32_t setFlip(std::uint32_t chn, bool b) = 0;

    virtual std::int32_t getImageColor(ImageColor& color) = 0;
    virtual std::int32_t setImageColor(const ImageColor& color) = 0;
    
    virtual int32_t aeQueryExposureInfo(AEExpoInfo *data) = 0;

    virtual int32_t aeSetEvComp(AEEvComp *data) = 0;
    virtual int32_t aeGetEvComp(AEEvComp *data) = 0;
    virtual int32_t aeSetExpoMode(AEMode_e mode) = 0;
    virtual int32_t aeGetExpoMode(AEMode_e &mode) = 0;
    virtual int32_t setCaptureShutter(uint32_t shutterInUs) = 0;
    virtual int32_t getCaptureShutter() = 0;
    virtual int32_t setCaptureIso(uint32_t iso) = 0;
    virtual int32_t getCaptureIso() = 0;
    virtual int32_t setVideoShutter(uint32_t shutterInUs) = 0;
    virtual int32_t getVideoShutter() = 0;
    virtual int32_t setVideoIso(uint32_t iso) = 0;
    virtual int32_t getVideoIso() = 0;
    virtual int32_t aeSetManualExpo(AEExpoValue *data) = 0;
    virtual int32_t aeGetManualExpo(AEExpoValue *data) = 0;

    virtual int32_t aeSetWinWgtType(AEWinWeightMode_e data,Coordinates *pCoordinates = NULL) = 0;
    virtual int32_t aeGetWinWgtType(AEWinWeightMode_e &data) = 0;

    virtual int32_t aeSetFlicker(AEFlickerType_e data) = 0;
    virtual int32_t aeGetFlicker(AEFlickerType_e &data) = 0;

    virtual int32_t awbQueryInfo(AWBQueryInfo *pData) = 0;
    virtual int32_t awbSetMode(AWBModeType_e mode) = 0;
    virtual int32_t awbSetEffect(AWBHueEffect_e effect) = 0;

    virtual std::int32_t enableChannel(std::uint32_t chn, bool enable) = 0;
    //std::int32_t enableChannel(std::int32_t w, std::int32_t h, bool enable);

    virtual std::int32_t enableOSD(std::uint32_t chn, std::uint32_t OSDId, bool enable) = 0;
    virtual std::int32_t setOSDPos(std::uint32_t chn, std::uint32_t OSDId, std::int32_t x, std::int32_t y) = 0;
    virtual std::int32_t setOSDText(std::uint32_t chn, std::uint32_t OSDId, const std::string& text) = 0;
    virtual std::int32_t setOSDFontSize(std::uint32_t chn, std::uint32_t OSDId, std::uint32_t fontSize) = 0;
    virtual std::int32_t setOSDFontColor(std::uint32_t chn, std::uint32_t OSDId, std::uint8_t a, std::uint8_t r, std::uint8_t g, std::uint8_t b) = 0;
    
    /* src dst都为0时表示恢复到未缩放状态 */
    virtual std::int32_t digitalZoom(std::uint32_t chn, const Rect& src, const Size& dst) = 0;
    
    /* 这里的chn 表示拍照时复用指定的chn的图像大小 zoom状态 OSD等信息 */
    virtual std::int32_t photograph(std::uint32_t chn, const PhotoInfo& info, const std::shared_ptr<IFrameQueue>& queue) = 0;
    virtual std::int32_t photoTerminate() = 0;
    /* 下面是一些辅助接口 */
    virtual std::int32_t findChannel(std::int32_t w, std::int32_t h, EncodeFmt fmt, std::uint32_t& chn) = 0;
    
    virtual std::int32_t digitalZoom(std::uint32_t chn, std::int32_t nx, std::int32_t cx = 50, std::int32_t cy = 50) = 0;
    
    virtual std::int32_t requestIdr(std::uint32_t chn) = 0;
};

#endif

