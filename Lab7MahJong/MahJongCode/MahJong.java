import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.KeyStroke;


public class MahJong extends JFrame implements MouseListener
{
	private MahJongBoard mjb;
	
	private long numberOfGame;
	
	protected static long[] games = {-1,-1,-1,-1,-1,-1,-1};
	
	private boolean newGame = false;
	
	
	public MahJong(long num)
	{
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		if(num == 0)
		{
			this.numberOfGame = System.currentTimeMillis() % 1000000; 
			add(mjb = new MahJongBoard(this.numberOfGame));
		}
		else if(num == games[sizeofGames()-1])
		{
			this.numberOfGame = num;
			add(mjb = new MahJongBoard(this.numberOfGame));
			newGame = true;
		}
		else
		{
			this.numberOfGame = num;
			add(mjb = new MahJongBoard(num));
		}
		
		if(!newGame)
			insertGame(this.numberOfGame);
		
		setSize(900,600);
		setTitle(printGames(1));
		makeMenu();
		setVisible(true);
	}
	
	public void play()
	{
		if (JOptionPane.showConfirmDialog(null, "Play New Game?",
				"Confirm Exit", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
		{
			this.dispose();
			mjb.frame.dispose();
			new MahJong(0);
		}	
	}
	
	public void restartGame()
	{
		if (JOptionPane.showConfirmDialog(null, "Restart Game?",
				"Confirm Exit", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
		{
			this.dispose();
			mjb.frame.dispose();
			new MahJong(this.numberOfGame);
		}	
	}
	
	public void undo()
	{
		mjb.undoT();
	}
	
	public void setOnVolume()
	{
		mjb.playClip = true;
	}
	
	public void setOffVolume()
	{
		mjb.playClip = false;
	}
	
	public void instructions()
	{
		Help	h = new Help("operation.html","Operation");
		h.display();	
	}
	public void gameRules()
	{
		Help	h = new Help("gameRules.html","Game Rules");
		h.display();	
	}
	
	public boolean validGame(long g)
	{
		int count = 0;
		while(games[count]!=-1)
		{
			if(games[count] == g)
				return true;
			count++;
			if(count == 6)
				break;
		}
		return false;
	}
	
	public void numbered()
	{
		long numberGame = 0;
		do {
			try {

				numberGame = Long.parseLong(JOptionPane.showInputDialog(printGames(0)));
				
			}
			catch(NumberFormatException e) {
				JOptionPane.showMessageDialog(null, "WRONG time of data!!! Try again");
			}
			
		}while(!validGame(numberGame) && numberGame != 0);
		if(numberGame == 0)
			return;
		this.dispose();
		mjb.frame.dispose();
		new MahJong(numberGame);
	}
	
	private void makeMenu()
	{
		JMenuBar	menuBar = new JMenuBar();
		setJMenuBar(menuBar);

		JMenu	gameMenu = new JMenu("Game");
		gameMenu.setMnemonic('G');
		menuBar.add(gameMenu);

		JMenuItem	play = new JMenuItem("Play", 'P');
		play.setToolTipText("Play Game");
		play.setAccelerator(KeyStroke.getKeyStroke("ctrl P"));
		gameMenu.add(play);
		play.addActionListener(new ActionListener()
		{ public void actionPerformed(ActionEvent e)
			{ 
			   play(); 
			}
		});
		
		JMenuItem	restart = new JMenuItem("Restart", 'R');
		restart.setToolTipText("Restart Game");
		restart.setAccelerator(KeyStroke.getKeyStroke("ctrl R"));
		gameMenu.add(restart);
		restart.addActionListener(new ActionListener()
		{ public void actionPerformed(ActionEvent e)
			{ 
			    restartGame(); 
			}
		});
		
		JMenuItem	numbered = new JMenuItem("Numbered", 'N');
		numbered.setToolTipText("Choose a game");
		numbered.setAccelerator(KeyStroke.getKeyStroke("ctrl N"));
		gameMenu.add(numbered);
		numbered.addActionListener(new ActionListener()
		{ public void actionPerformed(ActionEvent e)
			{ 
				numbered();
			}
		});
		
		ButtonGroup	group = new ButtonGroup();
		JMenu		soundMenu = new JMenu("Sound");
		soundMenu.setMnemonic('S');
		menuBar.add(soundMenu);
		
		JRadioButtonMenuItem	onSound = new JRadioButtonMenuItem("On", true);
		group.add(onSound);
		soundMenu.add(onSound);
		onSound.setToolTipText("Set On the volume");
		onSound.addActionListener(new ActionListener()
				{ public void actionPerformed(ActionEvent e)
					{ 
						setOnVolume();
					}
				});
	
		JRadioButtonMenuItem	offSound = new JRadioButtonMenuItem("Off", true);
		group.add(offSound);
		soundMenu.add(offSound);
		offSound.setToolTipText("Set Off the volume");
		offSound.setAccelerator(KeyStroke.getKeyStroke("ctrl O"));
		offSound.addActionListener(new ActionListener()
				{ public void actionPerformed(ActionEvent e)
					{ 
						setOffVolume();
					}
				});
		
		JMenu	moveMenu = new JMenu("Move");
		moveMenu.setMnemonic('M');
		menuBar.add(moveMenu);
		
		JMenuItem	undo = new JMenuItem("Undo", 'U');
		undo.setToolTipText("Undo Game");
		undo.setAccelerator(KeyStroke.getKeyStroke("ctrl U"));
		moveMenu.add(undo);
		undo.addActionListener(new ActionListener()
		{ public void actionPerformed(ActionEvent e)
			{ 
			  undo(); 
			}
		});
		
		JMenu	helpMenu = new JMenu("Help");
		helpMenu.setMnemonic('M');
		menuBar.add(helpMenu);
		
		JMenuItem	operation = new JMenuItem("Operation", 'O');
		operation.setToolTipText("Undo Game");
		helpMenu.add(operation);
		operation.addActionListener(new ActionListener()
		{ public void actionPerformed(ActionEvent e)
			{ 
			instructions();
			}
		});
		
		JMenuItem	gameRules = new JMenuItem("Game Rules", 'G');
		gameRules.setToolTipText("Game Rules");
		helpMenu.add(gameRules);
		gameRules.addActionListener(new ActionListener()
		{ public void actionPerformed(ActionEvent e)
			{ 
			gameRules(); 
			}
		});
		
		
	}
	
	public int sizeofGames()
	{
		int number = 0;
		while(games[number] != -1)
		{
			number++;
		}
		return number;
	}
	public void insertGame(long game) 
	{
		int number = sizeofGames();
		if(number < 6)
			games[number] = game;
		else
			moveGames(game);
	}
	public void moveGames(long game)
	{
		for(int i = 0; i < 5; i++)
		{
			games[i] = games[i+1];
		}
		games[5] = game;
	}
	public String printGames(int option)
	{
		int count = 0;
		String text = "";
		if(option == 0)
			text = "Last Games Played\n";
		else
			text = "Last Games Played: ";
		while(games[count]!=-1)
		{
			String textGame = Long.toString(games[count]);
			if(option == 0)
				text = text  + textGame + "\n";
			else
				text = text  + textGame + ", ";
			count++;
			if(count == 6)
				break;
		}
		if(option == 0)
			text = text + "Please type one:";
		
		return text;
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	
	public static void main(String[] args)
	{

		new MahJong(0);
	}

}
