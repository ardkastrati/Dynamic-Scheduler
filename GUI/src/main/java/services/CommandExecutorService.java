/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.Channel;
import model.commands.ICommand;
import javafx.concurrent.Service;
import javafx.concurrent.Task;

/**
 *
 * @author ardkastrati
 */
public class CommandExecutorService extends Service {

    private ICommand command;
    private Channel channel;
    
    public CommandExecutorService(ICommand command, Channel channel) {
        this.command = command;
        this.channel = channel;
    }
    
    public void setCommand(ICommand command) {
        this.command = command;
    }
    @Override
    protected Task createTask() {
        //TODO: implement send commands via Shell
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    
}
