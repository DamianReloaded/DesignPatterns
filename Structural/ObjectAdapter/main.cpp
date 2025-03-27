/**
 * @brief Object Adapter Pattern Example
 * 
 * The Object Adapter Pattern allows for an interface of one class to be adapted to
 * a different interface of another class. The adapter wraps the existing object and
 * delegates the call to the adapted interface, making incompatible interfaces compatible.
 * 
 * Key Concepts:
 * - The adapter acts as a wrapper around an existing object.
 * - Delegates method calls to the wrapped object to make it compatible with the target interface.
 * - Allows existing classes to work with interfaces they weren't originally designed to work with.
 * 
 * Benefits:
 * - Provides flexibility in working with legacy code without modifying it.
 * - Allows different objects to work together even if they have incompatible interfaces.
 * - Reduces the need to subclass and allows you to compose behavior at runtime.
 */

 #include <iostream>
 #include <memory>
 
 // Target interface: Expected interface by the client
 class MediaPlayer
 {
 public:
     virtual void playAudio() = 0; ///< Method to play audio
     virtual ~MediaPlayer() = default; ///< Virtual destructor
 };
 
 // Adaptee: Existing class with incompatible interface
 class AudioPlayer
 {
 public:
     void playAudioFile()
     {
         std::cout << "Playing audio file" << std::endl; ///< Method to play audio file
     }
 };
 
 // Object Adapter: Adapts the AudioPlayer class to the MediaPlayer interface
 class MediaPlayerAdapter : public MediaPlayer
 {
 public:
     explicit MediaPlayerAdapter(std::shared_ptr<AudioPlayer> audioPlayer)
         : m_audioPlayer(std::move(audioPlayer)) {}
 
     void playAudio() override
     {
         m_audioPlayer->playAudioFile(); ///< Delegates the call to the AudioPlayer object
     }
 
 private:
     std::shared_ptr<AudioPlayer> m_audioPlayer; ///< Wrapped AudioPlayer object
 };
 
 // Client code
 int main()
 {
     // Create an instance of AudioPlayer
     auto m_audioPlayer = std::make_shared<AudioPlayer>();
 
     // Adapt the AudioPlayer to MediaPlayer using the Object Adapter
     std::shared_ptr<MediaPlayer> m_mediaPlayer = std::make_shared<MediaPlayerAdapter>(m_audioPlayer);
 
     // Use the adapted object (MediaPlayer interface) to play audio
     m_mediaPlayer->playAudio();
 
     return 0;
 }
 