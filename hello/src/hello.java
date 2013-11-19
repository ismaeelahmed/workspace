import java.applet.Applet;
import java.awt.Graphics;


public class hello extends Applet {
	public void paint (Graphics g){
		//g.drawString("hello World", getWidth()/2, getHeight()/2);
		g.drawRect(10,10,200,100);
		
	}

	@Override
	public void paintComponents(Graphics g) {
		// TODO Auto-generated method stub
		super.paintComponents(g);
	}

//	public static void main(String[] args){
//	System.out.println("Hello World");	
//	}
}
