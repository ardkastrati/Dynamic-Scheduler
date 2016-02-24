/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MOAB;

import com.jcraft.jsch.Channel;
import java.util.ArrayList;
import javafx.scene.control.Control;
import model.commands.ICommand;

/**
 *
 * @author ardkastrati
 */
public class Showbf implements ICommand {

    @Override
    public String getCommand() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }


    @Override
    public ArrayList<String> getScriptCommands() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    
    public String toString() {
        return "showbf";
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
