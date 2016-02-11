/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MPI;


import java.util.ArrayList;
import java.util.LinkedList;
import model.commands.ICommand;

/**
 *
 * @author ardkastrati
 */
public class MpiRun implements ICommand {

    private LinkedList<String> parameters = new LinkedList<String>();
    private String programName;
    
    
    public void setParameter(String parameter) {
        parameters.add(parameter);
    }
           
    @Override
    public String getCommand() {
        StringBuilder command = new StringBuilder();
        command.append("mpirun ");
        
        for (String parameter : parameters) {
            command.append(parameter);
            command.append(" ");
        }
        command.append(programName);
        return command.toString();
    }

    @Override
    public ArrayList<String> getScriptCommands() {
        ArrayList<String> scriptCommands = new ArrayList<>();
        scriptCommands.add(getCommand());
        return scriptCommands;
    }

    @Override
    public String toString() {
       return "mpirun";
    }
    
    /**
     *
     * @param command
     * @return
     */
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }
    
}
