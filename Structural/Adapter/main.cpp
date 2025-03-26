/**
 * @brief Adapter pattern example to demonstrate how to convert an interface into another expected interface.
 *
 * The Adapter pattern allows incompatible interfaces to work together by creating an intermediary 
 * (the Adapter) that adapts one interface to another.
 *
 * **Key Concepts:**
 * 1. **Target (`MediaPlayer`)**: The interface that the client expects.
 * 2. **Adaptee (`OldMediaPlayer`)**: The existing interface that needs to be adapted.
 * 3. **Adapter (`MediaAdapter`)**: The class that adapts the old interface to the new one, making them compatible.
 *
 * **How it works:**
 * 1. `OldMediaPlayer` provides an existing interface for playing media (e.g., `playOldMedia`).
 * 2. `MediaPlayer` is the interface that the client expects (e.g., `play`).
 * 3. `MediaAdapter` implements the `MediaPlayer` interface and internally uses an instance of `OldMediaPlayer` to call the old interface.
 * 4. The client can now use `MediaPlayer` interface to interact with both new and old media players seamlessly.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 /**
  * @brief Target interface, expected by the client.
  * 
  * This is the new interface that the client expects to use for playing media. 
  * It provides a `play` method which is intended to be used for any media playback.
  */
 class MediaPlayer
 {
 public:
     virtual ~MediaPlayer() = default;
 
     /**
      * @brief Play media with the given file name.
      * 
      * @param fileName The name of the media file to play.
      */
     virtual void play(const std::string &fileName) = 0;
 };
 
 /**
  * @brief Adaptee class, an old interface that needs to be adapted.
  * 
  * The `OldMediaPlayer` is the existing media player with a different method signature 
  * that needs to be adapted to the `MediaPlayer` interface.
  */
 class OldMediaPlayer
 {
 public:
     /**
      * @brief Play old media format.
      * 
      * This method can only play media in the old format.
      * 
      * @param fileName The name of the media file in the old format.
      */
     void playOldMedia(const std::string &fileName)
     {
         std::cout << "Playing old media: " << fileName << std::endl;
     }
 };
 
 /**
  * @brief Adapter class that adapts `OldMediaPlayer` to `MediaPlayer`.
  * 
  * The `MediaAdapter` adapts the old interface of `OldMediaPlayer` to the new `MediaPlayer`
  * interface, allowing the client to use both old and new media players seamlessly.
  */
 class MediaAdapter : public MediaPlayer
 {
 public:
     /**
      * @brief Constructor that takes a shared pointer to an `OldMediaPlayer`.
      * 
      * @param oldPlayer A shared pointer to an instance of `OldMediaPlayer`.
      */
     explicit MediaAdapter(std::shared_ptr<OldMediaPlayer> oldPlayer)
         : oldPlayer_(oldPlayer) {}
 
     /**
      * @brief Play media by adapting the call to the `OldMediaPlayer`'s method.
      * 
      * This method calls `playOldMedia` on the `OldMediaPlayer` instance, allowing 
      * the old media format to be played via the `MediaPlayer` interface.
      * 
      * @param fileName The name of the media file.
      */
     void play(const std::string &fileName) override
     {
         oldPlayer_->playOldMedia(fileName);
     }
 
 private:
     std::shared_ptr<OldMediaPlayer> oldPlayer_; ///< The `OldMediaPlayer` instance being adapted.
 };
 
 /**
  * @brief Client code that expects a `MediaPlayer` interface.
  * 
  * The client will use the `MediaPlayer` interface to play media, but it can work with both
  * the new `MediaPlayer` implementations and the old ones through the `MediaAdapter`.
  */
 void playMedia(std::shared_ptr<MediaPlayer> mediaPlayer, const std::string &fileName)
 {
     mediaPlayer->play(fileName);
 }
 
 int main()
 {
     // Create a shared pointer to an OldMediaPlayer
     auto oldPlayer = std::make_shared<OldMediaPlayer>();
 
     // Adapt the OldMediaPlayer to the MediaPlayer interface using the MediaAdapter
     std::shared_ptr<MediaPlayer> mediaAdapter = std::make_shared<MediaAdapter>(oldPlayer);
 
     // Client code can now interact with the MediaPlayer interface
     playMedia(mediaAdapter, "old_song.mp3");
 
     return 0;
 }
 