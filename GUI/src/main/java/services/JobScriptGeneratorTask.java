/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import controller.MOABScene.DirectoryChooserSceneController;
import controller.MOABScene.MpirunSceneController;
import controller.MOABScene.MsubController;
import java.util.ArrayList;
import javafx.concurrent.Task;;
import model.commands.MOAB.Msub;
import model.commands.MPI.MpiRun;

/**
 *
 * @author ardkastrati
 */
public class JobScriptGeneratorTask extends Task<ArrayList<String>> {

   
    public static final String moabCommands = "        #### MOAB commands";
    public static final String directoryCommand = "        ##### Directory";
    public static final String shellCommands = "        #### MPI commands";
    public static final String msubPrefix = "#MSUB ";
    
    private MsubController msubController;
    private MpirunSceneController mpirunController;
    private DirectoryChooserSceneController directoryController;
    
    @Override
    protected ArrayList<String> call() throws Exception {
     
        ArrayList<String> lines = new ArrayList<>();
        
        System.out.println(moabCommands);
        lines.add(moabCommands);
        updateProgress(1, 6);
        
        lines.add("");
        System.out.println("msub");
        System.out.println(msubController);
        Msub msubCommand = msubController.createMsubFromDataInGUI();
        updateMessage("Msub command successfully parsed");
        
        updateProgress(2, 6);
        
        
        ArrayList<String> msubCommandParameters = msubCommand.getScriptCommands();
        for(String line : msubCommandParameters) {
            lines.add(msubPrefix + line);
        }
        updateMessage("Msub script command generated");
        updateProgress(3, 6);
        
        lines.add("");
        lines.add("");
        lines.add(directoryCommand);
        lines.add("");
        lines.add(directoryController.getDirectory());
        updateMessage("Directory successfully parsed");
        updateProgress(4, 6);
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
        
        return lines;
    }

    public void setControllers(MsubController msubController, MpirunSceneController mpirunController, 
                               DirectoryChooserSceneController directoryController) {
        this.msubController = msubController;
        this.mpirunController = mpirunController;
        this.directoryController = directoryController;
        
    }
    

}
