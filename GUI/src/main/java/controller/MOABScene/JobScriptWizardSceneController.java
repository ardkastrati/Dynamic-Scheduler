package controller.MOABScene;

/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */

import controller.Controller;
import controller.LoadSceneHelper;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Pagination;
import javafx.util.Callback;
import model.JobScript;
import model.commands.CommandException;
import services.JobScriptGeneratorTask;

/**
 * The JobScriptWizardSceneController class controls the Job Script Wizard FXML
 * scene, which helps the user to generate a script command by using a wizard.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class JobScriptWizardSceneController implements Initializable, Controller {

	// The job script wizard scene has multiple pages which are separated and controlled using pagination
	@FXML
	Pagination commandPages;
        
        setPages();
    } 
    
    private void setPages() {
        commandPages.setPageFactory(new Callback<Integer, Node>() {
            @Override
            public Node call(Integer pageIndex) {
               Node node = setPage(pageIndex);
               return node;
            }
        });
    }
    private Node setPage(int index) {
        
        LoadSceneHelper loaderHelper = new LoadSceneHelper();
        FXMLLoader loader = null;
        Node node = null;
        if(currentCommandController != null) { currentCommandController.onExit();}
        
        try {
             
            switch(index) {
               
                case 0: 
                    if(firstNode == null) {
                      loader = loaderHelper.loadScene("MSUB");
                      node = loader.load();
                      firstNode = node;
                      msubController = loader.getController();
                    } else {
                      node = firstNode;
                    } 
                    msubController.onEntry();
                    currentCommandController = msubController;
                    break;
                case 1:
                    if(secondNode == null) {
                        loader = loaderHelper.loadScene("DirectoryChooser");
                        node = loader.load();
                        secondNode = node;
                        directoryChooserController = loader.getController();
                    //MySession.getInstant().sessionStatusProperty().addListener(listener);
                    } else {
                        node = secondNode;
                    }
                    directoryChooserController.onEntry();
                    currentCommandController = directoryChooserController;
                    break;
                case 2:
                    if(thirdNode == null) {
                     loader = loaderHelper.loadScene("MPIRUN");
                     node = loader.load();
                     thirdNode = node;
                     mpirunController = loader.getController();
                    } else {
                        node = thirdNode;
                    }
                    mpirunController.onEntry();
                    currentCommandController = mpirunController;
                    break;
                default:
                    assert false : this;
                    break;
            }
        } catch (IOException ex) {
           // Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE, null, ex);
        }
        return node;
    }

	private MsubController msubController;
	private MpirunSceneController mpirunController;
	private DirectoryChooserSceneController directoryChooserController;

	// the current controller which the user is interacting with
	private Controller currentCommandController;

	private JobScript jobScript;

        
	private Node firstNode = null;
	private Node secondNode = null;
	private Node thirdNode = null;
        
	/**
	 * Initializes the controller class.
	 */
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		setPages();
	}

	private void setPages() {
		commandPages.setPageFactory(new Callback<Integer, Node>() {
			@Override
			public Node call(Integer pageIndex) {
				Node node = setPage(pageIndex);
				return node;
			}
		});
	}

	// loads the matching scene for a page when it gets changed by the user
	private Node setPage(int index) {
		LoadSceneHelper loaderHelper = new LoadSceneHelper();
		FXMLLoader loader = null;
		Node node = null;
		if (currentCommandController != null) {
			currentCommandController.onExit();
		}

		try {
			// Choose which page (scene) to load based on the page index
			switch (index) {
			case 0:
				if (firstNode == null) {
					loader = loaderHelper.loadScene("MSUB");
					node = loader.load();
					firstNode = node;
					msubController = loader.getController();
				} else {
					node = firstNode;
				}
				msubController.onEntry();
				currentCommandController = msubController;
				break;
			case 1:
				if (secondNode == null) {
					loader = loaderHelper.loadScene("DirectoryChooser");
					node = loader.load();
					secondNode = node;
					directoryChooserController = loader.getController();
					// MySession.getInstant().sessionStatusProperty().addListener(listener);
				} else {
					node = secondNode;
				}
				directoryChooserController.onEntry();
				currentCommandController = directoryChooserController;
				break;
			case 2:
				if (thirdNode == null) {
					loader = loaderHelper.loadScene("MPIRUN");
					node = loader.load();
					thirdNode = node;
					mpirunController = loader.getController();
				} else {
					node = thirdNode;
				}
				mpirunController.onEntry();
				currentCommandController = mpirunController;
				break;
			default:
				assert false : this;
				break;
			}
		} catch (IOException|CommandException ex) {
			// Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE,
			// null, ex);
		}
		return node;
	}

	

	/**
	 * Called when the user tries to generate a command after he finishes
	 * interacting with the job script generation wizard
	 */
	
	public JobScriptGeneratorTask createGeneratorTask() {
		// Create a task for generating the script based on the user choices
		// made in the wizard
		JobScriptGeneratorTask generatorTask = new JobScriptGeneratorTask(msubController, mpirunController, directoryChooserController);
                return generatorTask;
	}
        
	public String getOnNextText() {
		return "Generate Script";
	}


	/**
	 * Returns the Job Script
	 * 
	 * @return the Job Script
	 * @see model.JobScript
	 */
	public JobScript getJobScript() {
		return this.jobScript;
	}
       

	/**
	 * Called when the scene is loaded
	 */
	public void onEntry() {
		if (commandPages != null) {
		   commandPages.setCurrentPageIndex(0);
		}
		currentCommandController.onEntry();
	}

	@Override
	public void onExit() {
            currentCommandController.onExit();
	}
}