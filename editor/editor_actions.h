//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#ifndef editor_actions_hpp
#define editor_actions_hpp

#include "panels_manager.h"
#include "vector3.h"
#include "filesystem.h"
#include "scene_forward.h"
#include <tinyxml2.h>

namespace vox {
namespace editor {
/**
 * A set of editor actions
 */
class EditorActions {
public:
    /**
     * Constructor
     */
    EditorActions(ui::PanelsManager& p_panelsManager);
    
    //MARK: - TOOLS
public:
    /**
     * Returns the panels manager
     */
    ui::PanelsManager& panelsManager();
    
    //MARK: - SETTINGS
public:
    /**
     * A simple enumeration that define two actor spawn modes
     */
    enum class ActorSpawnMode { ORIGIN, FRONT };
    
    /**
     * Defines if new actors should be spawned at origin
     */
    void setActorSpawnAtOrigin(bool value);
    
    /**
     * Defines how new actors should be spawned
     */
    void setActorSpawnMode(ActorSpawnMode value);
    
    /**
     * Reset the editor layout
     */
    void resetLayout();
    
    /**
     * Defines the scene view camera speed
     */
    void setSceneViewCameraSpeed(int speed);
    
    /**
     * Returns the scene view camera speed
     */
    int sceneViewCameraSpeed();
    
    /**
     * Defines the asset view camera speed
     */
    void setAssetViewCameraSpeed(int p_speed);
    
    /**
     * Returns the asset view camera speed
     */
    int assetViewCameraSpeed();
    
    /**
     * Resets the scene view camera position to the default one
     */
    void resetSceneViewCameraPosition();
    
    /**
     * Resets the scene view camera position to the default one
     */
    void resetAssetViewCameraPosition();
    
    //MARK: - GAME
public:
    /**
     * Defines some states for the editor
     */
    enum class EditorMode { EDIT, PLAY, PAUSE, FRAME_BY_FRAME };
    
    /**
     * Returns the current editor state/mode
     */
    EditorMode currentEditorMode() const;
    
    /**
     * Defines the editor state/mode
     */
    void setEditorMode(EditorMode newEditorMode);
    
    /**
     * Start playing the current scene and update the editor mode
     */
    void startPlaying();
    
    /**
     * Pause the current playing scene and update the editor mode
     */
    void pauseGame();
    
    /**
     * Stop platying the current scene and update the editor mode
     */
    void stopPlaying();
    
    /**
     * Play the current frame and pause the editor
     */
    void nextFrame();
    
    //MARK: - Entity_CREATION_DESTRUCTION
public:
    /**
     * Create an actor with the given component type
     */
    template<typename T>
    EntityPtr createMonoComponentActor(bool p_focusOnCreation = true, EntityPtr p_parent = nullptr);
    
    /**
     * Calculate the position where to spawn the actor using the current camera position and forward
     */
    Vector3F calculateActorSpawnPoint(float p_distanceToCamera);
    
    /**
     * Create an empty actor
     */
    EntityPtr createEmptyActor(bool p_focusOnCreation = true,
                               EntityPtr p_parent = nullptr, const std::string& p_name = "");
    
    /**
     * Create an actor with a model renderer and a material renderer. The model renderer with use the model identified
     * by the given path
     */
    EntityPtr createActorWithModel(const std::string& p_path, bool p_focusOnCreation = true,
                                   EntityPtr p_parent = nullptr, const std::string& p_name = "");
    
    /**
     * Destroy an actor from his scene
     */
    bool destroyActor(EntityPtr p_actor);
    
    /**
     * Duplicate an actor
     */
    void duplicateActor(EntityPtr p_toDuplicate, EntityPtr p_forcedParent = nullptr, bool p_focus = true);
    
    
    //MARK: - ENTITY_MANIPULATION
public:
    /**
     * Select an actor and show him in inspector
     */
    void selectActor(EntityPtr& p_target);
    
    /**
     * Unselect any selected actor and clearing the inspector
     */
    void unselectActor();
    
    /**
     * Returns true if any actor is selected
     */
    bool isAnyActorSelected() const;
    
    /**
     * Returns the selected actor. Make sur you verified that an actor is selected
     * with IsAnyActorSelected() before calling this method
     */
    EntityPtr getSelectedActor() const;
    
    /**
     * Moves the camera to the target actor
     */
    void moveToTarget(EntityPtr& p_target);
    
    //MARK: - RESOURCE_MANAGEMENT
public:
    /**
     * Compile every loaded shaders
     */
    void compileShaders();
    
    /**
     * Save every materials to their respective files
     */
    void saveMaterials();
    
    /**
     * Import an asset
     */
    bool importAsset(const std::string& p_initialDestinationDirectory);
    
    /**
     * Import an asset at location
     */
    bool importAssetAtLocation(const std::string& p_destination);
    
    /**
     * Returns the real path of a resource (complete absolute path)
     */
    std::string getRealPath(const std::string& p_path);
    
    /**
     * Returns the resource path of a file
     */
    std::string getResourcePath(const std::string& p_path, bool p_isFromEngine = false);
    
    /**
     * Returns the script path of a file
     */
    std::string getScriptPath(const std::string& p_path);
    
    /**
     * Propagate the folder rename everywhere (Resource manager, scenes, materials...)
     */
    void propagateFolderRename(std::string p_previousName, const std::string p_newName);
    
    /**
     * Propagate the folder destruction everywhere (Resource manager, scenes, materials...)
     */
    void propagateFolderDestruction(std::string p_folderPath);
    
    /**
     * Propagate the script rename in scenes and inspector
     */
    void propagateScriptRename(std::string p_previousName, std::string p_newName);
    
    /**
     * Propagate the file rename everywhere it is used
     */
    void propagateFileRename(std::string p_previousName, std::string p_newName);
    
    /**
     * Propagate the file rename through concerned files
     */
    void propagateFileRenameThroughSavedFilesOfType(const std::string& p_previousName, const std::string& p_newName,
                                                    fs::FileType p_fileType);
    
    
    //MARK: - SCENE
public:
    /**
     * Load an empty scene. Any unsaved changes to the current scene will be discarded
     */
    void loadEmptyScene();
    
    /**
     * Save the current scene to the given path
     */
    void saveCurrentSceneTo(const std::string& p_path);
    
    /**
     * Load a scene from the disk
     */
    void loadSceneFromDisk(const std::string& p_path, bool p_absolute = false);
    
    /**
     * Returns true if the current scene has been loaded from disk
     */
    bool isCurrentSceneLoadedFromDisk() const;
    
    /**
     * Save the current scene to its disk location
     */
    void saveSceneChanges();
    
    /**
     * Save the current scene to a new disk location (Can create a duplication of the scene file)
     */
    void saveAs();
    
    //MARK: - SCRIPTING
public:
    /**
     * Refresh every scripts (Re-interpret)
     */
    void refreshScripts();
    
    
    //MARK: - BUILDING
public:
    /**
     * Ask the user to select the build folder
     */
    std::optional<std::string> selectBuildFolder();
    
    /**
     * Build the current project
     */
    void build(bool p_autoRun = false, bool p_tempFolder = false);
    
    /**
     * Build the current project at the given location
     */
    void buildAtLocation(const std::string& p_configuration, const std::string p_buildPath, bool p_autoRun = false);
    
    //MARK: - ACTION_SYSTEM
    /**
     * Prepare an action for a future call
     */
    void delayAction(std::function<void()> p_action, uint32_t p_frames = 1);
    
    /**
     * Execute every actions that should be executed at this frame (Decrement the frame counter for each actions)
     */
    void executeDelayedActions();
    
public:
    Event<EntityPtr> actorSelectedEvent;
    Event<EntityPtr> actorUnselectedEvent;
    Event<EditorMode> editorModeChangedEvent;
    Event<> playEvent;
    
private:
    ui::PanelsManager& _panelsManager;
    
    ActorSpawnMode _actorSpawnMode = ActorSpawnMode::ORIGIN;
    EditorMode _editorMode = EditorMode::EDIT;
    
    std::vector<std::pair<uint32_t, std::function<void()>>> _delayedActions;
    
    tinyxml2::XMLDocument _sceneBackup;
};


}
}
#include "editor_actions-inl.h"

#endif /* editor_actions_hpp */
