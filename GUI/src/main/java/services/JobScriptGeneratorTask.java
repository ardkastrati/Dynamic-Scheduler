/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import controller.MOABScene.DirectoryChooserSceneController;
import controller.MOABScene.MpirunSceneController;
import controller.MOABScene.MsubController;
import java.util.ArrayList;
import javafx.concurrent.Task;import javafx.scene.control.TextArea;
;
import model.commands.MOAB.Msub;
import model.commands.MPI.MpiRun;

/**
 * A task for generating a script from the wizard.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class JobScriptGeneratorTask extends Task<ArrayList<String>> {

   
    public static final String moabCommands = "        #### MOAB commands";
    public static final String directoryCommand = "        ##### Directory";
    public static final String shellCommands = "        #### MPI commands";
    public static final String msubPrefix = "#MSUB ";
    
    private final MsubController msubController;
    private final MpirunSceneController mpirunController;
    private final DirectoryChooserSceneController directoryController;
    
    
    /**
     * The constructor of this task.
     * @param msubController msubController which controls the msub command
     * @param mpirunController mpirunController which controls the mpirun command
     * @param directoryController directoryController which controls the directory
     */ 
    public JobScriptGeneratorTask(MsubController msubController, MpirunSceneController mpirunController, 
                                  DirectoryChooserSceneController directoryController) {
        this.msubController = msubController;
        this.mpirunController = mpirunController;
        this.directoryController = directoryController;
    }
    
    /**
     * Runs the task and created an array of lines for the script.
     * Note that this method is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     * @return the lines of the scrip
     * @throws java.lang.Exception
     */
    @Override
    protected ArrayList<String> call() throws Exception {
     
        ArrayList<String> lines = new ArrayList<>();
        
        lines.add(moabCommands);
        updateProgress(1, 6);
        Thread.sleep(100);
        lines.add("");
        
        Msub msubCommand = msubController.createMsubFromDataInGUI();
        updateMessage("Msub command successfully parsed");
        
        updateProgress(2, 6);
        Thread.sleep(100);
        
        ArrayList<String> msubCommandParameters = msubCommand.getScriptCommands();
        for(String line : msubCommandParameters) {
            lines.add(msubPrefix + line);
        }
        updateMessage("Msub script command generated");
        updateProgress(3, 6);
        Thread.sleep(100);
        lines.add("");
        lines.add("");
        lines.add(directoryCommand);
        lines.add("");
        lines.add(directoryController.getDirectory());
        updateMessage("Directory successfully parsed");
        updateProgress(4, 6);
        Thread.sleep(100);
        lines.add("");
        lines.add("");
        lines.add(shellCommands);
        lines.add("");
        MpiRun mpirun = mpirunController.createMpirunFromDataInGUI();
        updateMessage("Mpirun command successfully parsed");
        updateProgress(5, 6);
        ArrayList<String> mpirunCommandParameters = mpirun.getScriptCommands();
        for(String line : mpirunCommandParameters) {
            lines.add(line);
        }
        updateMessage("Mpirun script command generated");
        updateProgress(6, 6);
        Thread.sleep(100);
        return lines;
    }

}
