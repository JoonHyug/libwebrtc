#ifndef LIB_WEBRTC_FFMPEG_VIDEO_ENCODER_H_
#define LIB_WEBRTC_FFMPEG_VIDEO_ENCODER_H_

#include <memory>
#include <vector>

#include "api/video/video_frame.h"
#include "api/video_codecs/video_codec.h"
#include "api/video_codecs/video_encoder.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "api/video_codecs/video_frame_type.h"

namespace libwebrtc {

class FfmpegVideoEncoder : public webrtc::VideoEncoder {
 public:
  FfmpegVideoEncoder() = default;
  ~FfmpegVideoEncoder() override = default;

  int InitEncode(const webrtc::VideoCodec* codec_settings,
                 const Settings& settings) override;

  int32_t Encode(
      const webrtc::VideoFrame& frame,
      const std::vector<webrtc::VideoFrameType>* frame_types) override;

  int32_t RegisterEncodeCompleteCallback(
      webrtc::EncodedImageCallback* callback) override;

  int32_t Release() override;

  EncoderInfo GetEncoderInfo() override;

 private:
  webrtc::EncodedImageCallback* callback_ = nullptr;
};

class FfmpegVideoEncoderFactory : public webrtc::VideoEncoderFactory {
 public:
  std::unique_ptr<webrtc::VideoEncoder> CreateVideoEncoder(
      const webrtc::SdpVideoFormat& format) override;

  std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const override;

  CodecInfo QueryVideoEncoder(
      const webrtc::SdpVideoFormat& format) const override;
};

}  // namespace libwebrtc

#endif  // LIB_WEBRTC_FFMPEG_VIDEO_ENCODER_H_
