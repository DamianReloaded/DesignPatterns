/**
 * @brief Class Adapter Pattern Example
 * 
 * The Class Adapter Pattern allows one class to adapt the interface of another
 * class through inheritance. The adapter class inherits from both the target
 * interface and the adaptee, thus making it possible to adapt the interface
 * using class inheritance.
 * 
 * Key Concepts:
 * - The adapter class inherits from both the target interface and the adaptee.
 * - The adapter delegates calls from the target interface to the adaptee.
 * - It allows the adaptee to be used where the target interface is expected.
 * 
 * Benefits:
 * - Simplifies code by using inheritance to adapt an existing class.
 * - No need for explicit delegation through composition, unlike the Object Adapter.
 * - Can be used when you need to adapt an object in a simpler inheritance-based way.
 */

 #include <iostream>
 #include <memory>
 
 // Target Interface: Expected interface by the client
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
 
 // Class Adapter: Adapts the AudioPlayer to MediaPlayer interface using inheritance
 class MediaPlayerAdapter : public MediaPlayer, private AudioPlayer
 {
 public:
     void playAudio() override
     {
         playAudioFile(); ///< Delegates the call to the inherited AudioPlayer's playAudioFile method
     }
 };
 
 // Client code
 int main()
 {
     // Create an instance of MediaPlayerAdapter, which adapts AudioPlayer
     std::shared_ptr<MediaPlayer> m_mediaPlayer = std::make_shared<MediaPlayerAdapter>();
 
     // Use the adapter object to play audio
     m_mediaPlayer->playAudio();
 
     return 0;
 }
 