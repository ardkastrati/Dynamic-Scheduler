/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands;

import com.jcraft.jsch.Channel;
import java.util.ArrayList;

/**
 *
 * @author ardkastrati
 */
public interface ICommand {
    
    
    public String getCommand();
    
    public ArrayList<String> getScriptCommands();
    
    public boolean equals(ICommand command);
    
}
