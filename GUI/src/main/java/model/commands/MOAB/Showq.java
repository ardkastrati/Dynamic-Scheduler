/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MOAB;

import java.util.ArrayList;
import model.commands.ICommand;

/**
 *
 * @author ardkastrati
 */
public class Showq implements ICommand {

    @Override
    public String getCommand() {
        return "showq";
    }
    
    
    /**
     *
     * @param command
     * @return
     */
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }

    @Override
    public ArrayList<String> getScriptCommands() {
        return null;
    }
}
