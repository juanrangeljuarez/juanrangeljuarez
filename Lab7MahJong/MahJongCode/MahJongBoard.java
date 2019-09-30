import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.net.URL;
import java.util.Stack;

import javax.swing.ImageIcon;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import	java.awt.*;

public class MahJongBoard extends JPanel implements MouseListener
{
	private MahJongModel mjm;
	private Tile first = null;
	private Stack<Tile> tileStack = new Stack<Tile>();
	private ImageIcon image;
	PlayClip clip = new PlayClip("audio/stone-scraping.wav", true);
	private	static	final	Dimension	SIZE = new Dimension(600,600);
	ScrollDemo	demo = new ScrollDemo();
	static JFrame		frame = new JFrame();
	public boolean playClip = true;
	private int zOrder1;
	private int zOrder2;
	private int win = 143;

	
	public MahJongBoard(long numGame)
	{
		setLayout(null);
		
	
		mjm = new MahJongModel(this,numGame);		
		
		URL    url = PictureTile.class.getResource("images/dragon_bg.png");
        image = new ImageIcon(url);
        image = new ImageIcon(image.getImage().				// Resize ImageIcon
				getScaledInstance((int)(image.getIconWidth()*1.2), -1, Image.SCALE_SMOOTH));

		setPreferredSize(SIZE);
		removedTiles();
	}
	
	
	
	public void removedTiles()
	{
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(demo);
		frame.setSize(400, 250);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		frame.setLocation(dim.width-(dim.width/3), dim.height/2-this.getSize().height/2);
		frame.setTitle("Removed Tiles");
		frame.setVisible(true);
	}
	
	
	@Override
	public void mouseClicked(MouseEvent e) {
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		Tile t = (Tile)e.getSource();
		boolean flagNotEqual = false;
		boolean tileRemoved = false;
		if(first != null)
		{
			if((t.getXDim() == first.getXDim() && t.getYDim() == first.getYDim() && t.getZDim() == first.getZDim()))
				flagNotEqual = true;
		}
		
		if((mjm.isTileOpen(t.getXDim(), t.getYDim(), t.getZDim())) && flagNotEqual == false)
		{
			
			if (first == null)							// select the clicked puzzle piece
			{
				first = t;
				first.tileSelected = true;
				repaint();
				
				return;
			}
			else if (t.matches(first))							// deselect the clicked puzzple piece
			{			
				mjm.deleteTile(t.getXDim(), t.getYDim(), t.getZDim());
				mjm.deleteTile(first.getXDim(), first.getYDim(), first.getZDim());
				
				t.setZOrder(getComponentZOrder(t));
				
				remove(t);	// other side of add
			    win--;
				first.setZOrder(getComponentZOrder(first));

				revalidate();
				
				remove(first);	// other side of add
				win--;
				revalidate();
				
				repaint();
				demo.addToUndo(first, t);					
				
				tileStack.push(t);
				tileStack.push(first);
				first.tileSelected = false;
				t.tileSelected = false;
				
				tileRemoved = true;
				if(playClip)
					clip.play();	
				if(win <= 0)
				{
					fire();
				}
				first = null;
				return;
			}
			first.tileSelected = false;
			first = null;
			
			repaint();
		}
		if(tileRemoved)
		{
			t.paint = false;
			first.paint = false;
			t = null;
			first = null;
		}		
	}
	
	public void undoT()
	{
		mjm.undoTile();
		mjm.undoTile();
		Tile t = (Tile)tileStack.pop();
		add(t);		
		setComponentZOrder(t,t.getZOrder());
		mjm.positionTile(t.getXDim(), t.getYDim(), t.getZDim(),zOrder1);
		t.paint =true;
		Tile t2 = (Tile)tileStack.pop();
		add(t2);
		setComponentZOrder(t2,t2.getZOrder());
		mjm.positionTile(t2.getXDim(), t2.getYDim(), t2.getZDim(),zOrder2);
		t2.paint =true;
		repaint();
		win++;
		win++;
		demo.repaint();
	}
	
	
	
	public void fire()
	{
		JFrame		frame = new JFrame();
		Fireworks	fw = new Fireworks();
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1000, 800);
		frame.add(fw.getPanel());
		frame.setVisible(true);

		fw.setExplosions(0, 1000);
		fw.fire();


		try
		{
			Thread.sleep(10000);
			fw.stop();
		}
		catch (InterruptedException ie) {}
	}
	
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("Mouse pressed");
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("Mouse pressed");
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawImage(image.getImage(), 16, 6, this);
		repaint();

	}

}