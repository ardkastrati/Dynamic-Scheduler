/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller;

import javafx.fxml.FXMLLoader;


/**
 *
 * @author ardkastrati
 */
public class LoadSceneHelper {
    
    /**
     *
     * @param command
     * @return
     */
    public FXMLLoader loadScene(String command) {
        FXMLLoader loader = null;
         switch(command) {
                case "CREATE SCRIPT":
                    loader = new FXMLLoader(getClass().getResource("/fxml/JobScriptCreatorScene.fxml"));
                    break;
                case "MSUB" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/MsubScene.fxml"));
                    break;
                case "SHOWQ" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/ShowqScene.fxml"));
                    break;
                case "SHOWSTART" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/ShowstartScene.fxml"));
                    break;
                case "CHECKJOB" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/CheckjobScene.fxml"));
                    break;
                case "MJOBCTL" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/MjobctlScene.fxml"));
                    break;
                case "SHOWBF" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/ShowbfScene.fxml"));
                    break;
                case "MPIRUN" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/MpirunScene.fxml"));
                    break;
                case "MODULE LOAD" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/ModuleLoadScene.fxml"));
                    break;
                case "MODULE UNLOAD" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/ModuleUnloadScene.fxml"));
                    break;
                case "MODULE AVAIL" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/ModuleAvailScene.fxml"));
                    break;
                case "MODULE LIST" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/ModuleListScene.fxml"));
                    break;
                case "DirectoryChooser" :
                    loader = new FXMLLoader(getClass().getResource("/fxml/DirectoryChooserScene.fxml"));
                    break;
                case "JobScript" :
                    loader = new FXMLLoader(getClass().getResource("fxml/JobScriptScene.fxml"));
                    break;
                default:
                // This way the code is protected against later changes, e.g.
                // introduction of new types in this enumeration type.
                assert false : this;
                break;
            }
       
        return loader;
        
    }
    
    
   
    
}
