#include "ffmpeg/ffmpeg_video_encoder.h"

namespace libwebrtc {

int FfmpegVideoEncoder::InitEncode(const webrtc::VideoCodec* /*codec_settings*/,
                                   const Settings& /*settings*/) {
  // TODO: Initialize FFmpeg encoder context here.
  return WEBRTC_VIDEO_CODEC_OK;
}

int32_t FfmpegVideoEncoder::Encode(
    const webrtc::VideoFrame& /*frame*/,
    const std::vector<webrtc::VideoFrameType>* /*frame_types*/) {
  // TODO: Encode the frame using FFmpeg and deliver via callback_.
  if (callback_) {
    webrtc::EncodedImage encoded_image;
    webrtc::CodecSpecificInfo info;
    callback_->OnEncodedImage(encoded_image, &info);
  }
  return WEBRTC_VIDEO_CODEC_OK;
}

int32_t FfmpegVideoEncoder::RegisterEncodeCompleteCallback(
    webrtc::EncodedImageCallback* callback) {
  callback_ = callback;
  return WEBRTC_VIDEO_CODEC_OK;
}

int32_t FfmpegVideoEncoder::Release() {
  // TODO: Clean up FFmpeg resources.
  return WEBRTC_VIDEO_CODEC_OK;
}

webrtc::VideoEncoder::EncoderInfo FfmpegVideoEncoder::GetEncoderInfo() {
  EncoderInfo info;
  info.has_trusted_rate_controller = true;
  return info;
}

std::unique_ptr<webrtc::VideoEncoder>
FfmpegVideoEncoderFactory::CreateVideoEncoder(
    const webrtc::SdpVideoFormat& /*format*/) {
  return std::make_unique<FfmpegVideoEncoder>();
}

std::vector<webrtc::SdpVideoFormat>
FfmpegVideoEncoderFactory::GetSupportedFormats() const {
  return {webrtc::SdpVideoFormat(cricket::kH264CodecName)};
}

webrtc::VideoEncoderFactory::CodecInfo
FfmpegVideoEncoderFactory::QueryVideoEncoder(
    const webrtc::SdpVideoFormat& /*format*/) const {
  CodecInfo info;
  info.has_internal_source = false;
  return info;
}

}  // namespace libwebrtc
