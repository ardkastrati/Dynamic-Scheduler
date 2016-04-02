
package services;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;
import javafx.concurrent.Task;
import model.MySession;

/**
 * A task for creating a new channel.
 *
 * @author ardkastrati
 * @version 1.0
 */

public class CreateNewChannelTask extends Task<Channel> {

    private final Session currentSession;
    private final String channelType;
    
    
    /**
     * The constructor of this task.
     * @param session the session where to create the channel
     * @param channelType the type of channel
     */ 
    public CreateNewChannelTask(Session session, String channelType) {
        this.currentSession = session; 
        this.channelType = channelType;
    }
    /**
     * Runs the task which creates a new channel.
     * Note that this method is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     * @return the created channel.
     * @throws com.jcraft.jsch.JSchException
     */
    @Override
    protected Channel call() throws JSchException  {
       Channel channel;
       
        channel = currentSession.openChannel(channelType);
        updateMessage("Channel successfully opened!");
        channel.connect();
        updateMessage("Channel connected successfully");
       
       
        return channel;
    }
    
}
