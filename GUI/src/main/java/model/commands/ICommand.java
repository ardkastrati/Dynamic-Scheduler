
package model.commands;

import java.util.ArrayList;

/**
 * Defines a <tt>Command</tt> which can is used to represent the commands in the MOAB Workload Manager.
 * <p>
 * Users of this interface must implement the <code>getScriptCommands</code> method, which
 * return an array of lines representation of the command to be used in the shell script. 
 * </p>
 * @author ardkastrati
 * @version 1
 */
public interface ICommand {
    
    /**
     * This method must return a string representation of the command.
     * @return string representation of the command.
     */ 
    public String getCommand();
    
    /**
     * This method must return an array of lines, which are used to write the command in the shell script.
     * @return 
     */
    public ArrayList<String> getScriptCommands();
    
}
