/**
 * @brief Memento Pattern example for an Undo/Redo Text Editor.
 *
 * **Key Concepts:**
 * 1. **Originator (`TextEditor`)**: The object whose state needs to be saved and restored.
 * 2. **Memento (`EditorMemento`)**: Stores the state of the originator.
 * 3. **Caretaker (`HistoryManager`)**: Manages the history of mementos for undo/redo functionality.
 *
 * **Benefits:**
 * - Provides a way to save and restore an object's state without exposing its internal structure.
 * - Enables undo/redo functionality efficiently.
 * - Decouples state management from the main object.
 */

 #include <iostream>
 #include <memory>
 #include <stack>
 #include <string>
 
 /**
  * @brief Memento class that stores the state of the text editor.
  */
 class EditorMemento
 {
 public:
     explicit EditorMemento(std::string state) : m_state(std::move(state)) {}
 
     /**
      * @brief Retrieves the stored state.
      * @return The stored text.
      */
     std::string getState() const
     {
         return m_state;
     }
 
 private:
     std::string m_state; ///< Stored text content.
 };
 
 /**
  * @brief The Originator, representing a text editor.
  */
 class TextEditor
 {
 public:
     /**
      * @brief Sets the text in the editor.
      * @param text The new text.
      */
     void setText(const std::string& text)
     {
         m_text = text;
     }
 
     /**
      * @brief Gets the current text.
      * @return The current text in the editor.
      */
     std::string getText() const
     {
         return m_text;
     }
 
     /**
      * @brief Saves the current state to a memento.
      * @return A shared pointer to a memento storing the current state.
      */
     std::shared_ptr<EditorMemento> save() const
     {
         return std::make_shared<EditorMemento>(m_text);
     }
 
     /**
      * @brief Restores the editor's state from a memento.
      * @param memento The memento to restore from.
      */
     void restore(std::shared_ptr<EditorMemento> memento)
     {
         if (memento)
         {
             m_text = memento->getState();
         }
     }
 
 private:
     std::string m_text; ///< Current text content in the editor.
 };
 
 /**
  * @brief The Caretaker that manages undo/redo functionality.
  */
 class HistoryManager
 {
 public:
     /**
      * @brief Saves a snapshot of the editor's state.
      * @param memento The memento storing the state.
      */
     void saveState(std::shared_ptr<EditorMemento> memento)
     {
         m_undoStack.push(memento);
         m_redoStack = std::stack<std::shared_ptr<EditorMemento>>(); // Clear redo stack on new action
     }
 
     /**
      * @brief Undoes the last change.
      * @param editor The text editor to apply the undo operation on.
      */
     void undo(TextEditor& editor)
     {
         if (!m_undoStack.empty())
         {
             m_redoStack.push(editor.save());
             editor.restore(m_undoStack.top());
             m_undoStack.pop();
         }
     }
 
     /**
      * @brief Redoes the last undone change.
      * @param editor The text editor to apply the redo operation on.
      */
     void redo(TextEditor& editor)
     {
         if (!m_redoStack.empty())
         {
             m_undoStack.push(editor.save());
             editor.restore(m_redoStack.top());
             m_redoStack.pop();
         }
     }
 
 private:
     std::stack<std::shared_ptr<EditorMemento>> m_undoStack; ///< Stack of undo states.
     std::stack<std::shared_ptr<EditorMemento>> m_redoStack; ///< Stack of redo states.
 };
 
 /**
  * @brief Demonstrates the text editor with undo/redo using the Memento Pattern.
  */
 int main()
 {
     TextEditor editor;
     HistoryManager history;
 
     editor.setText("Hello");
     history.saveState(editor.save());
 
     editor.setText("World");
     history.saveState(editor.save());
 
     editor.setText("!");
     history.saveState(editor.save());
 
     std::cout << "Current text: " << editor.getText() << "\n";
 
     history.undo(editor);
     std::cout << "After undo: " << editor.getText() << "\n";
 
     history.undo(editor);
     std::cout << "After undo: " << editor.getText() << "\n";
 
     history.undo(editor);
     std::cout << "After undo: " << editor.getText() << "\n";
 
     history.redo(editor);
     std::cout << "After redo: " << editor.getText() << "\n";
 
     history.redo(editor);
     std::cout << "After redo: " << editor.getText() << "\n";
 
     return 0;
 }
 