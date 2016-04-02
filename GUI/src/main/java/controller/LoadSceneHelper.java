
package controller;

import javafx.fxml.FXMLLoader;
import model.commands.CommandException;

/**
 * The LoadSceneHelper class contains helper methods to load different scenes
 * based on user choices in the GUI.
 * 
 * @author ardkastrati
 * @version 1.0
 */
public class LoadSceneHelper {

	/**
	 * Loads a scene based on the given command (user choice)
	 * 
	 * @param command
	 *            the given command as chosen by the user in GUI
	 * @return the FXMLLoader object containing the matching scene
	 * @see javafx.fxml.FXMLLoader
	 */
	public FXMLLoader loadScene(String command) throws CommandException {
		FXMLLoader loader = null;
		switch (command) {
		case "CREATE SCRIPT":
			loader = new FXMLLoader(getClass().getResource("/fxml/JobScriptCreatorScene.fxml"));
			break;
		case "MSUB":
			loader = new FXMLLoader(getClass().getResource("/fxml/MsubScene.fxml"));
			break;
		case "SHOWQ":
			//loader = new FXMLLoader(getClass().getResource("/fxml/ShowqScene.fxml"));
                        throw new CommandException("This command is not supported yet");
		case "SHOWSTART":
			//loader = new FXMLLoader(getClass().getResource("/fxml/ShowstartScene.fxml"));
			throw new CommandException("This command is not supported yet");
		case "CHECKJOB":
			//loader = new FXMLLoader(getClass().getResource("/fxml/CheckjobScene.fxml"));
			throw new CommandException("This command is not supported yet");
		case "MJOBCTL":
			//loader = new FXMLLoader(getClass().getResource("/fxml/MjobctlScene.fxml"));
			throw new CommandException("This command is not supported yet");
		case "SHOWBF":
			//loader = new FXMLLoader(getClass().getResource("/fxml/ShowbfScene.fxml"));
			throw new CommandException("This command is not supported yet");
		case "MPIRUN":
			loader = new FXMLLoader(getClass().getResource("/fxml/MpirunScene.fxml"));
			break;
		case "MODULE LOAD":
			//loader = new FXMLLoader(getClass().getResource("/fxml/ModuleLoadScene.fxml"));
			throw new CommandException("This command is not supported yet");
		case "MODULE UNLOAD":
			//loader = new FXMLLoader(getClass().getResource("/fxml/ModuleUnloadScene.fxml"));
			throw new CommandException("This command is not supported yet");
		case "MODULE AVAIL":
			loader = new FXMLLoader(getClass().getResource("/fxml/ModuleAvailScene.fxml"));
			break;
		case "MODULE LIST":
			//loader = new FXMLLoader(getClass().getResource("/fxml/ModuleListScene.fxml"));
			break;
		case "DirectoryChooser":
			loader = new FXMLLoader(getClass().getResource("/fxml/DirectoryChooserScene.fxml"));
			break;
		case "JobScript":
			loader = new FXMLLoader(getClass().getResource("/fxml/JobScriptScene.fxml"));
			break;
                case "ValidateCommand":
                        loader = new FXMLLoader(getClass().getResource("/fxml/CommandValidationScene.fxml"));
                        break;
		default:
			// This way the code is protected against later changes, e.g.
			// introduction of new scenes in this program.
			assert false : this;
			break;
		}
		return loader;
	}
}