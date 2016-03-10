/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.Compile;

import model.commands.ICommand;
import java.util.ArrayList;

 /**
    * This enum represents the possible types of the module command in MOAB Workload Manager.<br/>
    * The following list specifies the allowed paramters in {@code module} command:
    * <p>
    *  <ul>
    *   <li>LOAD</li>
    *   <li>UNLOAD</li>
    *   <li>AVAIL</li>
    *   <li>LIST</li>
    *  </ul>
    * </p>
    * @author ardkastrati
    * @version 1.0
    *
    */
public enum Module implements ICommand{
    
    LOAD("load") {

        @Override
        public String toString() {
           return "module load";
        }
        
    },
    UNLOAD("unload") {

        @Override
        public String toString() {
           return "module unload";
        }
        
    },
    AVAIL("avail") {

        @Override
        public String toString() {
           return "module avail";
        }
        
    },
    LIST("list") {
        @Override
        public String toString() {
            return "module list";
        }
        
    };
    
    private String command;
    
    private Module(String command) {
        this.command = command;
    }

    @Override
    public String getCommand() {
        throw new UnsupportedOperationException("Not supported yet."); 
    }

    @Override
    public ArrayList<String> getScriptCommands() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    /**
     * Compares to ICommands lexiographically and ignores case.
     * @param command
     * @return true if the command is lexiographically the same.
     */
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }
    
    
    
}
