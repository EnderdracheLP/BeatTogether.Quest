#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <future>

namespace UnityEngine::Networking {
    class UnityWebRequest;
}

namespace BTDownloader {
    // Forward declarations
    class BeatSaver;
    class SongDownloadingTask;
    struct DownloadedSong;

    using SongDownloadingTaskPtr = std::shared_ptr<SongDownloadingTask>;
    using BeatSaverHash = std::string;

    class BeatSaver {
    public:
        SongDownloadingTaskPtr downloadSongWithHash(const BeatSaverHash& hash);
        static BeatSaver& sharedInstance();

    private:
        std::unordered_map<BeatSaverHash, SongDownloadingTaskPtr> downloadTasks;
    };

    struct DownloadedSong {
    public:
        std::string levelPath;
        std::string hash;
    };

    class SongDownloadingTask {
    public:
        using DownloadError = uint8_t;

        std::string hash;
        std::optional<std::exception> downloadException;

        explicit SongDownloadingTask(std::string hash);
                    

        void onCompletion(std::function<void(const DownloadedSong&, const DownloadError)> handler);

        static std::string getCustomSongFolder();

    private:
        std::vector<std::function<void(const DownloadedSong&, const DownloadError)>> completionHandlers;
        std::promise<DownloadedSong> result;
        std::shared_future<DownloadedSong> future;
        std::mutex handlersMutex {};

    private:
        friend class BeatSaver;
        class UnityEngine::Networking::UnityWebRequest* webRequest;

        void onDownloadTaskCompletion();
    };
}
