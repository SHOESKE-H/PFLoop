#ifndef PFLOOP_SRC_VIDEO_VIDEO_READER_HPP
#define PFLOOP_SRC_VIDEO_VIDEO_READER_HPP

#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <src/Video/Frame.hpp>
#include <vector>
#include <stdexcept>

class VideoReader
{
public:
    VideoReader() noexcept
        : m_videoCap() {}

    VideoReader(const std::string& t_path)
        : m_videoCap(t_path)
        {
            if (!m_videoCap.isOpened())
                throw std::runtime_error("Video file not open.");
        }

    std::vector<Frame> extractFrames(void)
    {
        std::vector<Frame> frames;
        frames.reserve(m_videoCap.get(cv::CAP_PROP_FRAME_COUNT));
        for (int i = 0; i < m_videoCap.get(cv::CAP_PROP_FRAME_COUNT); i++) {
            Frame frame;
            m_videoCap >> frame;
            frames.push_back(frame);
        }

        return frames;
    }

private:
    cv::VideoCapture m_videoCap;
};

#endif // PFLOOP_SRC_VIDEO_VIDEO_READER_HPP
