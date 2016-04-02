/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MOAB;

import java.util.ArrayList;
import javafx.scene.control.Control;
import model.commands.ICommand;

/**
 *
 * @author ardkastrati
 */
public class Mjobctl extends Control implements ICommand {

    
    public String getCommand() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }


    @Override
    public ArrayList<String> getScriptCommands() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    
    public String toString() {
       return "mjobctl";
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
