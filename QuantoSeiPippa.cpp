// QuantoSeiPippa.cpp : file di implementazione
//

#include "stdafx.h"
#include "prova.h"
#include "QuantoSeiPippa.h"
#include "common.h"
#include "XLEzAutomation.h"
#include "XLAutomation.h"
#include "lassificaSuperPippa.h"


ClassificaSuperPippa ClassificaP_Dialog;


#define F433 0
#define F442 1
#define F532 2
#define F541 3
#define F352 4

struct aux_voti
{
	int tipo;
	float voto;
};

struct aux_voti tmp_voti;
struct aux_voti auxvoti[5];


unsigned long idc_sqr[16] =
{
	IDC_SQR1, IDC_SQR2, IDC_SQR3, IDC_SQR4, IDC_SQR5,
	IDC_SQR6, IDC_SQR7, IDC_SQR8, IDC_SQR9, IDC_SQR10,
	IDC_SQR11, IDC_SQR12, IDC_SQR13, IDC_SQR14, IDC_SQR15, IDC_SQR16,
};
unsigned long idc_edit_sqr[16] =
{
	IDC_EDIT_SQR1, IDC_EDIT_SQR2, IDC_EDIT_SQR3, IDC_EDIT_SQR4, IDC_EDIT_SQR5,
	IDC_EDIT_SQR6, IDC_EDIT_SQR7, IDC_EDIT_SQR8, IDC_EDIT_SQR9, IDC_EDIT_SQR10,
	IDC_EDIT_SQR11, IDC_EDIT_SQR12, IDC_EDIT_SQR13, IDC_EDIT_SQR14, IDC_EDIT_SQR15, IDC_EDIT_SQR16,
};

struct incontro_struct A_day[5][2];
struct incontro_struct B_day[5][2];
struct squadra_struct SQRA[10];
struct squadra_struct SQRB[6];
struct SuperPippa SP_Squadre[16];
extern struct squadra_struct SquadreA[10];
extern struct squadra_struct SquadreB[6];
extern CString VotiMirror[15][500];
// finestra di dialogo QuantoSeiPippa

extern void conv2float(float *value, CString s1 );
extern W8 TCHARcmp(TCHAR *s1, TCHAR *s2);


////////////////////////////////////////////
void Presidente_goals(void)
{
	W8 aux_counter, cerca_counter, direzione;
    W8 gol_fatti, gol_subiti, gol_presidente;
	TCHAR Squadra_In[16], Squadra_Out[16];
	float voto_campionato, voto_avversario, voto_presidente;
    W8 trovato;    

	//serie A
	for(aux_counter=0; aux_counter<5; aux_counter++)
	{
		for(direzione=0; direzione<2;direzione++)
		{
			memcpy(Squadra_In, A_day[aux_counter][direzione].NomeSquadra, sizeof(TCHAR)*16);
			memcpy(Squadra_Out, A_day[aux_counter][(direzione==0)?1:0].NomeSquadra, sizeof(TCHAR)*16);
			voto_avversario = A_day[aux_counter][(direzione==0)?1:0].voto_netto;
			voto_campionato = A_day[aux_counter][direzione].voto_netto;
			gol_fatti = A_day[aux_counter][direzione].goal_fatti;
			gol_subiti = A_day[aux_counter][direzione].goal_subiti;
			trovato=0;
			cerca_counter=0;
			while(trovato==0)
			{
				if(TCHARcmp(Squadra_In, SQRA[cerca_counter].NomeSquadra)==0)
				{
					//trovato
					voto_presidente=SQRA[cerca_counter].voto_finale;
					trovato=1;
				}
				else
				{
					//non trovato
					cerca_counter++;
				}
			}
       		if(voto_presidente<66)
			{
				gol_presidente= ( (voto_avversario<60) && ( (voto_presidente-voto_avversario)> 3.5) ) ? 1 : 0;
			}
			else if(voto_presidente <72)
			{
					gol_presidente=1;
					gol_presidente += ( (voto_avversario>65.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
					gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
				}
				else if(voto_presidente < 78)
					{
						gol_presidente=2;
						gol_presidente += ( (voto_avversario>71.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
						gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
					}
					else if(voto_presidente < 84)
						{
							gol_presidente=3;
							gol_presidente += ( (voto_avversario>77.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
							gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
						}
						else if(voto_presidente < 90)
							{
								gol_presidente=4;
								gol_presidente += ( (voto_avversario>83.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
								gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
							}
							else
							{
								gol_presidente=5;
								gol_presidente += ( (voto_avversario>89.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
								gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
			}
			trovato=0;
			cerca_counter=0;
			while(trovato==0)
			{
				if(TCHARcmp(Squadra_In, SP_Squadre[cerca_counter].Squadra)==0)
				{
					//trovato
					trovato=1;
					//cerca_counter punta al valore da aggiornare
				}
				else
				{
					//non trovato
					cerca_counter++;
				}
			}
			if (gol_fatti <= gol_subiti)
			{
				if (gol_fatti == gol_subiti)
				{
					if (gol_presidente > gol_subiti)
						SP_Squadre[cerca_counter].voto +=2;
				}
				else if (gol_presidente > gol_subiti)
					    SP_Squadre[cerca_counter].voto +=3;
				else if (gol_presidente == gol_subiti)
					    SP_Squadre[cerca_counter].voto +=1;
			}
		}//ciclo direzione
	} //ciclo for sulle cinque linee della giornata
	//serie b
	for(aux_counter=0; aux_counter<3; aux_counter++)
	{
		for(direzione=0; direzione<2;direzione++)
		{
			memcpy(Squadra_In, B_day[aux_counter][direzione].NomeSquadra, sizeof(TCHAR)*16);
			memcpy(Squadra_Out, B_day[aux_counter][(direzione==0)?1:0].NomeSquadra, sizeof(TCHAR)*16);
			voto_avversario = B_day[aux_counter][(direzione==0)?1:0].voto_netto;
			voto_campionato = B_day[aux_counter][direzione].voto_netto;
			gol_fatti = B_day[aux_counter][direzione].goal_fatti;
			gol_subiti = B_day[aux_counter][direzione].goal_subiti;
			trovato=0;
			cerca_counter=0;
			while(trovato==0)
			{
				if(TCHARcmp(Squadra_In, SQRB[cerca_counter].NomeSquadra)==0)
				{
					//trovato
					voto_presidente=SQRB[cerca_counter].voto_finale;
					trovato=1;
				}
				else
				{
					//non trovato
					cerca_counter++;
				}
			}
       		if(voto_presidente<66)
			{
				gol_presidente= ( (voto_avversario<60) && ( (voto_presidente-voto_avversario)> 3.5) ) ? 1 : 0;
			}
			else if(voto_presidente <72)
			{
					gol_presidente=1;
					gol_presidente += ( (voto_avversario>65.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
					gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
				}
				else if(voto_presidente < 78)
					{
						gol_presidente=2;
						gol_presidente += ( (voto_avversario>71.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
						gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
					}
					else if(voto_presidente < 84)
						{
							gol_presidente=3;
							gol_presidente += ( (voto_avversario>77.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
							gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
						}
						else if(voto_presidente < 90)
							{
								gol_presidente=4;
								gol_presidente += ( (voto_avversario>83.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
								gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
							}
							else
							{
								gol_presidente=5;
								gol_presidente += ( (voto_avversario>89.5) && (voto_avversario<voto_presidente) && ((voto_presidente-voto_avversario)>3.5) ) ? 1 : 0;
								gol_presidente += ( (voto_presidente-voto_avversario)>9.5) ? 1 : 0;
			}
			trovato=0;
			cerca_counter=0;
			while(trovato==0)
			{
				if(TCHARcmp(Squadra_In, SP_Squadre[cerca_counter].Squadra)==0)
				{
					//trovato
					trovato=1;
					//cerca_counter punta al valore da aggiornare
				}
				else
				{
					//non trovato
					cerca_counter++;
				}
			}
			if (gol_fatti <= gol_subiti)
			{
				if (gol_fatti == gol_subiti)
				{
					if (gol_presidente > gol_subiti)
						SP_Squadre[cerca_counter].voto +=2;
				}
				else if (gol_presidente > gol_subiti)
					    SP_Squadre[cerca_counter].voto +=3;
				else if (gol_presidente == gol_subiti)
					    SP_Squadre[cerca_counter].voto +=1;
			}
		}//ciclo direzione
	} //ciclo for sulle tre linee della giornata
}
//////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(QuantoSeiPippa, CDialog)

QuantoSeiPippa::QuantoSeiPippa(CWnd* pParent /*=NULL*/)
	: CDialog(QuantoSeiPippa::IDD, pParent)
{

}

QuantoSeiPippa::~QuantoSeiPippa()
{
}

void QuantoSeiPippa::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GIORNATA, FinestraListaSquadre);
	DDX_Control(pDX, IDC_MostraSquadra, MostraSquadra);
}


BEGIN_MESSAGE_MAP(QuantoSeiPippa, CDialog)
	ON_BN_CLICKED(IDC_CALCOLA, &QuantoSeiPippa::OnBnClickedCalcola)
	ON_BN_CLICKED(IDC_MostraFormazione, &QuantoSeiPippa::OnBnClickedMostraformazione)
	ON_BN_CLICKED(IDC_AggiornaClassifica, &QuantoSeiPippa::OnBnClickedAggiornaclassifica)
	ON_BN_CLICKED(IDC_MostraGiornata, &QuantoSeiPippa::OnBnClickedMostragiornata)
	ON_BN_CLICKED(IDC_MOSTRA_SPC, &QuantoSeiPippa::OnBnClickedMostraSpc)
END_MESSAGE_MAP()


// gestori di messaggi QuantoSeiPippa

void QuantoSeiPippa::OnBnClickedCalcola()
{
	int i, j, which_team, which_player;
	struct giocatore_struct* playerA;
	struct giocatore_struct* playerB;
	struct giocatore_struct salva_giocatore;
	float voto1, voto2;
	float voto433, voto532, voto442, voto541, voto352;
	bool exit_flag;
	CString szValue, Txt;
	TCHAR senzavoto[]=L"6*";
	TCHAR tmp[4];
	float partial, total;

	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
	memcpy(SQRA, SquadreA, sizeof(squadra_struct)*10);
	memcpy(SQRB, SquadreB, sizeof(squadra_struct)*6);
    //dai un voto a tutti i componenti della rosa.
	for(which_team=0; which_team<10; which_team++)
	{
		//per ogni giocatore
		for(which_player=0; which_player<25;which_player++)
		{
			if(which_player<3)
			{
				playerA=&(SQRA[which_team].Portieri[which_player]);
				if(which_team < 6)
					playerB=&(SQRB[which_team].Portieri[which_player]);
			}
			else if(which_player<11)
			{
				playerA=&(SQRA[which_team].Difensori[which_player-3]);
				if(which_team < 6)
					playerB=&(SQRB[which_team].Difensori[which_player-3]);
			}
			else if(which_player<19)
			{
				playerA=&(SQRA[which_team].Centrocampisti[which_player-11]);
				if(which_team < 6)
					playerB=&(SQRB[which_team].Centrocampisti[which_player-11]);
			}
			else
			{
				playerA=&(SQRA[which_team].Attaccanti[which_player-19]);
				if(which_team < 6)
					playerB=&(SQRB[which_team].Attaccanti[which_player-19]);
			}
			playerA->Voto = 0;
			exit_flag=false;
			// per tutto il worksheet
			i=C_NOME;    // column
			for(j=1; (j<500 && !(exit_flag)); j++)  //row
			{
				szValue = VotiMirror[i][j];
				if(szValue == playerA->NomeGiocatore)
				{
					// got it!
					total=0;
					partial=0;
					szValue = VotiMirror[C_VOTO][j];
					szValue.CopyChars(tmp, 3, szValue, 3);
					tmp[3]=0;
					if(TCHARcmp(tmp, senzavoto))
					{
						conv2float(&(playerA->Voto), szValue );
//bonus
                        szValue = VotiMirror[C_GOAL_FATTO][j];
						conv2float(&partial, szValue);
						if(partial) total +=3*partial;
						partial=0;
						szValue = VotiMirror[C_RIGORE_PARATO][j];
						conv2float(&partial, szValue);
						if(partial) total +=3*partial;
						partial=0;
						szValue = VotiMirror[C_RIGORE_SEGNATO][j];
						conv2float(&partial, szValue);
						if(partial) total +=3*partial;
						playerA->Bonus = total;
//malus
						total=0;
						partial = 0;
						szValue = VotiMirror[C_GOAL_SUBITO][j];
						conv2float(&partial, szValue);
						if(partial) total += partial;
						partial = 0;
						szValue = VotiMirror[C_RIGORE_SBAGLIATO][j];
						conv2float(&partial, szValue);
						if(partial) total += 3*partial;
						partial=0;
						szValue = VotiMirror[C_AUTORETE][j];
						conv2float(&partial, szValue);
						if(partial) total += 2*partial;
						partial=0;
						szValue = VotiMirror[C_AMMONIZIONE][j];
						conv2float(&partial, szValue);
						if(partial) total += partial/2;
						partial=0;
						szValue = VotiMirror[C_ESPULSIONE][j];
						conv2float(&partial, szValue);
						if(partial) total += partial;
						playerA->Malus = -total;
						exit_flag=true;
					}
				}
			}
			playerB->Voto = 0;
			exit_flag=false;
			for(j=1; (j<500 && !(exit_flag)); j++) 
			{
				// per tutto il worksheet
				i=C_NOME;    // column
				szValue = VotiMirror[i][j];
				if(szValue == playerB->NomeGiocatore)
				{
					partial=0;
					total=0;
					// got it!
					szValue = VotiMirror[C_VOTO][j];
					szValue.CopyChars(tmp, 3, szValue, 3);
					tmp[3]=0;
					if(TCHARcmp(tmp, senzavoto))
					{
						conv2float(&(playerB->Voto), szValue );
//bonus
                        szValue = VotiMirror[C_GOAL_FATTO][j];
						conv2float(&partial, szValue);
						if(partial) total +=3*partial;
						partial=0;
						szValue = VotiMirror[C_RIGORE_PARATO][j];
						conv2float(&partial, szValue);
						if(partial) total +=3*partial;
						partial=0;
						szValue = VotiMirror[C_RIGORE_SEGNATO][j];
						conv2float(&partial, szValue);
						if(partial) total +=3*partial;
						playerB->Bonus = total;
//malus
						total=0;
						partial = 0;
						szValue = VotiMirror[C_GOAL_SUBITO][j];
						conv2float(&partial, szValue);
						if(partial) total += partial;
						partial = 0;
						szValue = VotiMirror[C_RIGORE_SBAGLIATO][j];
						conv2float(&partial, szValue);
						if(partial) total += 3*partial;
						partial=0;
						szValue = VotiMirror[C_AUTORETE][j];
						conv2float(&partial, szValue);
						if(partial) total += 2*partial;
						partial=0;
						szValue = VotiMirror[C_AMMONIZIONE][j];
						conv2float(&partial, szValue);
						if(partial) total += partial/2;
						partial=0;
						szValue = VotiMirror[C_ESPULSIONE][j];
						conv2float(&partial, szValue);
						if(partial) total += partial;
						playerB->Malus = -total;
						exit_flag=true;
					}
				}
			}
		}
	}
//per tutti i team di A
	for(which_team=0; which_team<10; which_team++)
	{
		//ordina per voto i portieri
		for(i=0; i<2; i++)
		{
			voto1= SQRA[which_team].Portieri[i].Voto + SQRA[which_team].Portieri[i].Bonus + SQRA[which_team].Portieri[i].Malus;
			for(j=i+1; j<3; j++)
			{
				voto2= SQRA[which_team].Portieri[j].Voto + SQRA[which_team].Portieri[j].Bonus + SQRA[which_team].Portieri[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRA[which_team].Portieri[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Portieri[i]), (void *)&(SQRA[which_team].Portieri[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Portieri[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1 = voto2;
				}
			}
		}
		//ordina per voto difensori
		for(i=0; i<7; i++)
		{
			voto1= SQRA[which_team].Difensori[i].Voto + SQRA[which_team].Difensori[i].Bonus + SQRA[which_team].Difensori[i].Malus;
			for(j=i+1; j<8; j++)
			{
				voto2= SQRA[which_team].Difensori[j].Voto + SQRA[which_team].Difensori[j].Bonus + SQRA[which_team].Difensori[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRA[which_team].Difensori[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Difensori[i]), (void*)&(SQRA[which_team].Difensori[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Difensori[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1 = voto2;
				}
			}
		}
		//ordina per voto centrocampisti
		for(i=0; i<7; i++)
		{
			voto1= SQRA[which_team].Centrocampisti[i].Voto + SQRA[which_team].Centrocampisti[i].Bonus + SQRA[which_team].Centrocampisti[i].Malus;
			for(j=i+1; j<8; j++)
			{
				voto2= SQRA[which_team].Centrocampisti[j].Voto + SQRA[which_team].Centrocampisti[j].Bonus + SQRA[which_team].Centrocampisti[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRA[which_team].Centrocampisti[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Centrocampisti[i]), (void*)&(SQRA[which_team].Centrocampisti[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Centrocampisti[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1=voto2;
				}
			}
		}
		//ordina per voto attaccanti
		for(i=0; i<5; i++)
		{
			voto1= SQRA[which_team].Attaccanti[i].Voto + SQRA[which_team].Attaccanti[i].Bonus + SQRA[which_team].Attaccanti[i].Malus;
			for(j=i+1; j<6; j++)
			{
				voto2= SQRA[which_team].Attaccanti[j].Voto + SQRA[which_team].Attaccanti[j].Bonus + SQRA[which_team].Attaccanti[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRA[which_team].Attaccanti[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Attaccanti[i]), (void*)&(SQRA[which_team].Attaccanti[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRA[which_team].Attaccanti[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1=voto2;
				}
			}
		}
	}
//per tutti i team di B
	for(which_team=0; which_team<6; which_team++)
	{
		//ordina per voto i portieri
		for(i=0; i<2; i++)
		{
			voto1= SQRB[which_team].Portieri[i].Voto + SQRB[which_team].Portieri[i].Bonus + SQRB[which_team].Portieri[i].Malus;
			for(j=i+1; j<3; j++)
			{
				voto2= SQRB[which_team].Portieri[j].Voto + SQRB[which_team].Portieri[j].Bonus + SQRB[which_team].Portieri[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRB[which_team].Portieri[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Portieri[i]), (void*)&(SQRB[which_team].Portieri[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Portieri[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1=voto2;
				}
			}
		}
		//ordina per voto difensori
		for(i=0; i<7; i++)
		{
			voto1= SQRB[which_team].Difensori[i].Voto + SQRB[which_team].Difensori[i].Bonus + SQRB[which_team].Difensori[i].Malus;
			for(j=i+1; j<8; j++)
			{
				voto2= SQRB[which_team].Difensori[j].Voto + SQRB[which_team].Difensori[j].Bonus + SQRB[which_team].Difensori[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRB[which_team].Difensori[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Difensori[i]), (void*)&(SQRB[which_team].Difensori[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Difensori[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1=voto2;
				}
			}
		}
		//ordina per voto centrocampisti
		for(i=0; i<7; i++)
		{
			voto1= SQRB[which_team].Centrocampisti[i].Voto + SQRB[which_team].Centrocampisti[i].Bonus + SQRB[which_team].Centrocampisti[i].Malus;
			for(j=i+1; j<8; j++)
			{
				voto2= SQRB[which_team].Centrocampisti[j].Voto + SQRB[which_team].Centrocampisti[j].Bonus + SQRB[which_team].Centrocampisti[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRB[which_team].Centrocampisti[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Centrocampisti[i]), (void*)&(SQRB[which_team].Centrocampisti[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Centrocampisti[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1=voto2;
				}
			}
		}
		//ordina per voto attaccanti
		for(i=0; i<5; i++)
		{
			voto1= SQRB[which_team].Attaccanti[i].Voto + SQRB[which_team].Attaccanti[i].Bonus + SQRB[which_team].Attaccanti[i].Malus;
			for(j=i+1; j<6; j++)
			{
				voto2= SQRB[which_team].Attaccanti[j].Voto + SQRB[which_team].Attaccanti[j].Bonus + SQRB[which_team].Attaccanti[j].Malus;
				if(voto2 > voto1)
				{
					memcpy((void*)&salva_giocatore, (void*)&(SQRB[which_team].Attaccanti[i]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Attaccanti[i]), (void*)&(SQRB[which_team].Attaccanti[j]), sizeof(giocatore_struct));
					memcpy((void*)&(SQRB[which_team].Attaccanti[j]), (void*)&salva_giocatore, sizeof(giocatore_struct));
					voto1=voto2;
				}
			}
		}
	}
//ora le squadre sono ordinate, dal giocatore con voto più alto a quello con voto più basso
	//comincia con la A
    for(which_team=0; which_team<10; which_team++)
	{
		//portiere sicuramente titolare
		SQRA[which_team].Portieri[0].flag_titolare = 1;
		SQRA[which_team].Portieri[1].flag_titolare = 0;
		SQRA[which_team].Portieri[2].flag_titolare = 0;
		voto1= SQRA[which_team].Portieri[0].Voto+ SQRA[which_team].Portieri[0].Bonus+ SQRA[which_team].Portieri[0].Malus;
		voto433=voto1; voto442=voto1; voto532=voto1; voto541=voto1; voto352=voto1;
		voto1= SQRA[which_team].Difensori[0].Voto+ SQRA[which_team].Difensori[0].Bonus+ SQRA[which_team].Difensori[0].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Difensori[1].Voto+ SQRA[which_team].Difensori[1].Bonus+ SQRA[which_team].Difensori[1].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Difensori[2].Voto+ SQRA[which_team].Difensori[2].Bonus+ SQRA[which_team].Difensori[2].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Difensori[3].Voto+ SQRA[which_team].Difensori[3].Bonus+ SQRA[which_team].Difensori[3].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1;
		voto1= SQRA[which_team].Difensori[4].Voto+ SQRA[which_team].Difensori[4].Bonus+ SQRA[which_team].Difensori[4].Malus;
		voto532+=voto1; voto541+=voto1;
		voto1= SQRA[which_team].Centrocampisti[0].Voto+ SQRA[which_team].Centrocampisti[0].Bonus+ SQRA[which_team].Centrocampisti[0].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Centrocampisti[1].Voto+ SQRA[which_team].Centrocampisti[1].Bonus+ SQRA[which_team].Centrocampisti[1].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Centrocampisti[2].Voto+ SQRA[which_team].Centrocampisti[2].Bonus+ SQRA[which_team].Centrocampisti[2].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Centrocampisti[3].Voto+ SQRA[which_team].Centrocampisti[3].Bonus+ SQRA[which_team].Centrocampisti[3].Malus;
		voto442+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Centrocampisti[4].Voto+ SQRA[which_team].Centrocampisti[4].Bonus+ SQRA[which_team].Centrocampisti[4].Malus;
		voto352+=voto1;
		voto1= SQRA[which_team].Attaccanti[0].Voto+ SQRA[which_team].Attaccanti[0].Bonus+ SQRA[which_team].Attaccanti[0].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Attaccanti[1].Voto+ SQRA[which_team].Attaccanti[1].Bonus+ SQRA[which_team].Attaccanti[1].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto352+=voto1;
		voto1= SQRA[which_team].Attaccanti[2].Voto+ SQRA[which_team].Attaccanti[2].Bonus+ SQRA[which_team].Attaccanti[2].Malus;
		voto433+=voto1;
		auxvoti[0].tipo = F433;
		auxvoti[0].voto = voto433;
		auxvoti[1].tipo = F442;
		auxvoti[1].voto = voto442;
		auxvoti[2].tipo = F532;
		auxvoti[2].voto = voto532;
		auxvoti[3].tipo = F541;
		auxvoti[3].voto = voto541;
		auxvoti[4].tipo = F352;
		auxvoti[4].voto = voto352;
		for(i=0;i<4;i++) {
			for(j=i+1;j<5;j++)
			{
				if(auxvoti[j].voto>auxvoti[i].voto)
				{
					memcpy(&tmp_voti, &(auxvoti[i]), sizeof(struct aux_voti));
					memcpy(&(auxvoti[i]), &(auxvoti[j]), sizeof(struct aux_voti));
					memcpy(&(auxvoti[j]), &tmp_voti, sizeof(struct aux_voti));
				}
			}
		}
        //ora auxvoti al primo posto è il punteggio più alto nello schieramento migliore
		SQRA[which_team].Difensori[0].flag_titolare = 1;
		SQRA[which_team].Difensori[1].flag_titolare = 1;
		SQRA[which_team].Difensori[2].flag_titolare = 1;
		if(auxvoti[0].tipo == F352)
		{
			SQRA[which_team].Difensori[3].flag_titolare = 0;
		}
		else
		{
			SQRA[which_team].Difensori[3].flag_titolare = 1;
		}
		if((auxvoti[0].tipo == F352) ||(auxvoti[0].tipo == F442) ||(auxvoti[0].tipo == F433))
		{
			SQRA[which_team].Difensori[4].flag_titolare = 0;
		}
		else
		{
			SQRA[which_team].Difensori[4].flag_titolare = 1;
		}
		SQRA[which_team].Difensori[5].flag_titolare = 0;
		SQRA[which_team].Difensori[6].flag_titolare = 0;
		SQRA[which_team].Difensori[7].flag_titolare = 0;
		SQRA[which_team].Centrocampisti[0].flag_titolare = 1;
		SQRA[which_team].Centrocampisti[1].flag_titolare = 1;
		SQRA[which_team].Centrocampisti[2].flag_titolare = 1;
		if( (auxvoti[0].tipo == F433) || (auxvoti[0].tipo == F532) ) 
		{
			SQRA[which_team].Centrocampisti[3].flag_titolare = 0;
		}
		else
		{
			SQRA[which_team].Centrocampisti[3].flag_titolare = 1;
		}
		if(auxvoti[0].tipo == F352)
		{
			SQRA[which_team].Centrocampisti[4].flag_titolare = 1;
		}
		else
		{
			SQRA[which_team].Centrocampisti[4].flag_titolare = 0;
		}
		SQRA[which_team].Centrocampisti[5].flag_titolare = 0;
		SQRA[which_team].Centrocampisti[6].flag_titolare = 0;
		SQRA[which_team].Centrocampisti[7].flag_titolare = 0;
		SQRA[which_team].Attaccanti[0].flag_titolare = 1;
		if(auxvoti[0].tipo == F541) 
		{
			SQRA[which_team].Attaccanti[1].flag_titolare = 0;
		}
		else
		{
			SQRA[which_team].Attaccanti[1].flag_titolare = 1;
		}
		if(auxvoti[0].tipo == F433)  
		{
			SQRA[which_team].Attaccanti[2].flag_titolare = 1;
		}
		else
		{
			SQRA[which_team].Attaccanti[2].flag_titolare = 0;
		}
		SQRA[which_team].Attaccanti[3].flag_titolare = 0;
		SQRA[which_team].Attaccanti[4].flag_titolare = 0;
		SQRA[which_team].Attaccanti[5].flag_titolare = 0;
		SQRA[which_team].voto_finale = auxvoti[0].voto;
	}
    //ripeti per la B	
    for(which_team=0; which_team<6; which_team++)
	{
		//portiere sicuramente titolare
		SQRB[which_team].Portieri[0].flag_titolare = 1;
		SQRB[which_team].Portieri[1].flag_titolare = 0;
		SQRB[which_team].Portieri[2].flag_titolare = 0;
		voto1= SQRB[which_team].Portieri[0].Voto+ SQRB[which_team].Portieri[0].Bonus+ SQRB[which_team].Portieri[0].Malus;
		voto433=voto1; voto442=voto1; voto532=voto1; voto541=voto1; voto352=voto1;
		voto1= SQRB[which_team].Difensori[0].Voto+ SQRB[which_team].Difensori[0].Bonus+ SQRB[which_team].Difensori[0].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Difensori[1].Voto+ SQRB[which_team].Difensori[1].Bonus+ SQRB[which_team].Difensori[1].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Difensori[2].Voto+ SQRB[which_team].Difensori[2].Bonus+ SQRB[which_team].Difensori[2].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Difensori[3].Voto+ SQRB[which_team].Difensori[3].Bonus+ SQRB[which_team].Difensori[3].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1;
		voto1= SQRB[which_team].Difensori[4].Voto+ SQRB[which_team].Difensori[4].Bonus+ SQRB[which_team].Difensori[4].Malus;
		voto532+=voto1; voto541+=voto1;
		voto1= SQRB[which_team].Centrocampisti[0].Voto+ SQRB[which_team].Centrocampisti[0].Bonus+ SQRB[which_team].Centrocampisti[0].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Centrocampisti[1].Voto+ SQRB[which_team].Centrocampisti[1].Bonus+ SQRB[which_team].Centrocampisti[1].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Centrocampisti[2].Voto+ SQRB[which_team].Centrocampisti[2].Bonus+ SQRB[which_team].Centrocampisti[2].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Centrocampisti[3].Voto+ SQRB[which_team].Centrocampisti[3].Bonus+ SQRB[which_team].Centrocampisti[3].Malus;
		voto442+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Centrocampisti[4].Voto+ SQRB[which_team].Centrocampisti[4].Bonus+ SQRB[which_team].Centrocampisti[4].Malus;
		voto352+=voto1;
		voto1= SQRB[which_team].Attaccanti[0].Voto+ SQRB[which_team].Attaccanti[0].Bonus+ SQRB[which_team].Attaccanti[0].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto541+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Attaccanti[1].Voto+ SQRB[which_team].Attaccanti[1].Bonus+ SQRB[which_team].Attaccanti[1].Malus;
		voto433+=voto1; voto442+=voto1; voto532+=voto1; voto352+=voto1;
		voto1= SQRB[which_team].Attaccanti[2].Voto+ SQRB[which_team].Attaccanti[2].Bonus+ SQRB[which_team].Attaccanti[2].Malus;
		voto433+=voto1;
		auxvoti[0].tipo = F433;
		auxvoti[0].voto = voto433;
		auxvoti[1].tipo = F442;
		auxvoti[1].voto = voto442;
		auxvoti[2].tipo = F532;
		auxvoti[2].voto = voto532;
		auxvoti[3].tipo = F541;
		auxvoti[3].voto = voto541;
		auxvoti[4].tipo = F352;
		auxvoti[4].voto = voto352;
		for(i=0;i<4;i++) {
			for(j=i+1;j<5;j++)
			{
				if(auxvoti[j].voto>auxvoti[i].voto)
				{
					memcpy(&tmp_voti, &(auxvoti[i]), sizeof(struct aux_voti));
					memcpy(&(auxvoti[i]), &(auxvoti[j]), sizeof(struct aux_voti));
					memcpy(&(auxvoti[j]), &tmp_voti, sizeof(struct aux_voti));
				}
			}
		}
        //ora auxvoti al primo posto è il punteggio più alto nello schieramento migliore
		SQRB[which_team].Difensori[0].flag_titolare = 1;
		SQRB[which_team].Difensori[1].flag_titolare = 1;
		SQRB[which_team].Difensori[2].flag_titolare = 1;
		if(auxvoti[0].tipo == F352)
		{
			SQRB[which_team].Difensori[3].flag_titolare = 0;
		}
		else
		{
			SQRB[which_team].Difensori[3].flag_titolare = 1;
		}
		if((auxvoti[0].tipo == F352) ||(auxvoti[0].tipo == F442) ||(auxvoti[0].tipo == F433))
		{
			SQRB[which_team].Difensori[4].flag_titolare = 0;
		}
		else
		{
			SQRB[which_team].Difensori[4].flag_titolare = 1;
		}
		SQRB[which_team].Difensori[5].flag_titolare = 0;
		SQRB[which_team].Difensori[6].flag_titolare = 0;
		SQRB[which_team].Difensori[7].flag_titolare = 0;
		SQRB[which_team].Centrocampisti[0].flag_titolare = 1;
		SQRB[which_team].Centrocampisti[1].flag_titolare = 1;
		SQRB[which_team].Centrocampisti[2].flag_titolare = 1;
		if( (auxvoti[0].tipo == F433) || (auxvoti[0].tipo == F532) ) 
		{
			SQRB[which_team].Centrocampisti[3].flag_titolare = 0;
		}
		else
		{
			SQRB[which_team].Centrocampisti[3].flag_titolare = 1;
		}
		if(auxvoti[0].tipo == F352)
		{
			SQRB[which_team].Centrocampisti[4].flag_titolare = 1;
		}
		else
		{
			SQRB[which_team].Centrocampisti[4].flag_titolare = 0;
		}
		SQRB[which_team].Centrocampisti[5].flag_titolare = 0;
		SQRB[which_team].Centrocampisti[6].flag_titolare = 0;
		SQRB[which_team].Centrocampisti[7].flag_titolare = 0;
		SQRB[which_team].Attaccanti[0].flag_titolare = 1;
		if(auxvoti[0].tipo == F541) 
		{
			SQRB[which_team].Attaccanti[1].flag_titolare = 0;
		}
		else
		{
			SQRB[which_team].Attaccanti[1].flag_titolare = 1;
		}
		if(auxvoti[0].tipo == F433)  
		{
			SQRB[which_team].Attaccanti[2].flag_titolare = 1;
		}
		else
		{
			SQRB[which_team].Attaccanti[2].flag_titolare = 0;
		}
		SQRB[which_team].Attaccanti[3].flag_titolare = 0;
		SQRB[which_team].Attaccanti[4].flag_titolare = 0;
		SQRB[which_team].Attaccanti[5].flag_titolare = 0;
		SQRB[which_team].voto_finale = auxvoti[0].voto;
	}
	MostraSquadra.ResetContent();
	for(which_team=0; which_team<10;which_team++)
	{
		Txt.Format(L"%-6s : %3.1f\n vs %3.1f >>> %3.1f", SQRA[which_team].NickName, 
			SQRA[which_team].voto_finale, SquadreA[which_team].voto_finale, 
			SQRA[which_team].voto_finale - SquadreA[which_team].voto_finale);
		MostraSquadra.AddString(Txt);
	}
	for(which_team=0; which_team<6;which_team++)
	{
		Txt.Format(L"%-6s : %3.1f\n vs %3.1f >>> %3.1f", SQRB[which_team].NickName, 
			SQRB[which_team].voto_finale, SquadreB[which_team].voto_finale, 
			SQRB[which_team].voto_finale - SquadreB[which_team].voto_finale);
		MostraSquadra.AddString(Txt);
	}
}

void QuantoSeiPippa::OnBnClickedMostraformazione()
{
	int i, j, t;
	CString Txt;
	BOOL CheckBoxFlag;

	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
    // CheckBoxFlag = IsDlgButtonChecked(idc_1c[i]);
    // unsigned long idc_sqr[16]
	//controlla la spunta
	Txt.Format(L"\n");
	MostraSquadra.AddString(Txt);
	for(i=0; i<16; i++)
	{
		if( CheckBoxFlag = IsDlgButtonChecked(idc_sqr[i]) )
		{
			if(i<10)
			{
				Txt.Format(L"%-30s\n", SQRA[i].NomeSquadra);
				MostraSquadra.AddString(Txt);
				//serie A
				//portiere
				Txt.Format(L"P %-25s %-3.1f\n", SQRA[i].Portieri[0].NomeGiocatore,
					SQRA[i].Portieri[0].Voto+SQRA[i].Portieri[0].Bonus+SQRA[i].Portieri[0].Malus);
				MostraSquadra.AddString(Txt);
				//difensori
				for(j=0;j<8;j++)
				{
					if(SQRA[i].Difensori[j].flag_titolare)
					{
						Txt.Format(L"D %-25s %-3.1f\n", SQRA[i].Difensori[j].NomeGiocatore,
							SQRA[i].Difensori[j].Voto+SQRA[i].Difensori[j].Bonus+SQRA[i].Difensori[j].Malus);
						MostraSquadra.AddString(Txt);
					}
				}
				//centrocampisti
				for(j=0;j<8;j++)
				{
					if(SQRA[i].Centrocampisti[j].flag_titolare)
					{
						Txt.Format(L"C %-25s %-3.1f\n", SQRA[i].Centrocampisti[j].NomeGiocatore,
							SQRA[i].Centrocampisti[j].Voto+SQRA[i].Centrocampisti[j].Bonus+SQRA[i].Centrocampisti[j].Malus);
						MostraSquadra.AddString(Txt);
					}
				}
				//attaccanti
				for(j=0;j<6;j++)
				{
					if(SQRA[i].Attaccanti[j].flag_titolare)
					{
						Txt.Format(L"A %-25s %-3.1f\n", SQRA[i].Attaccanti[j].NomeGiocatore,
							SQRA[i].Attaccanti[j].Voto+SQRA[i].Attaccanti[j].Bonus+SQRA[i].Attaccanti[j].Malus);
						MostraSquadra.AddString(Txt);
					}
				}
				//voto finale
				Txt.Format(L"\t\t VOTO FINALE : %-3.1f\n", SQRA[i].voto_finale);
				MostraSquadra.AddString(Txt);
			}
			else
			{
				//serie B
				t=i-10;
				Txt.Format(L"%-30s\n", SQRB[t].NomeSquadra);
				MostraSquadra.AddString(Txt);
				//serie A
				//portiere
				Txt.Format(L"P %-25s %-3.1f\n", SQRB[t].Portieri[0].NomeGiocatore,
					SQRB[t].Portieri[0].Voto+SQRB[t].Portieri[0].Bonus+SQRB[t].Portieri[0].Malus);
				MostraSquadra.AddString(Txt);
				//difensori
				for(j=0;j<8;j++)
				{
					if(SQRB[t].Difensori[j].flag_titolare)
					{
						Txt.Format(L"D %-25s %-3.1f\n", SQRB[t].Difensori[j].NomeGiocatore,
							SQRB[t].Difensori[j].Voto+SQRB[t].Difensori[j].Bonus+SQRB[t].Difensori[j].Malus);
						MostraSquadra.AddString(Txt);
					}
				}
				//centrocampisti
				for(j=0;j<8;j++)
				{
					if(SQRB[t].Centrocampisti[j].flag_titolare)
					{
						Txt.Format(L"C %-25s %-3.1f\n", SQRB[t].Centrocampisti[j].NomeGiocatore,
							SQRB[t].Centrocampisti[j].Voto+SQRB[t].Centrocampisti[j].Bonus+SQRB[t].Centrocampisti[j].Malus);
						MostraSquadra.AddString(Txt);
					}
				}
				//attaccanti
				for(j=0;j<6;j++)
				{
					if(SQRB[t].Attaccanti[j].flag_titolare)
					{
						Txt.Format(L"A %-25s %-3.1f\n", SQRB[t].Attaccanti[j].NomeGiocatore,
							SQRB[t].Attaccanti[j].Voto+SQRB[t].Attaccanti[j].Bonus+SQRB[t].Attaccanti[j].Malus);
						MostraSquadra.AddString(Txt);
					}
				}
				//voto finale
				Txt.Format(L"\t\t VOTO FINALE : %-3.1f\n", SQRB[t].voto_finale);
				MostraSquadra.AddString(Txt);
			}
		}
	}
}

void QuantoSeiPippa::OnBnClickedAggiornaclassifica()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
	extern void conv2float(float *value, CString s1 );
	CString szValue;
	CString szFileName;
	int Row, i, limit;
	struct SuperPippa Aux;

    CXLEzAutomation XL(FALSE);
	CXLEzAutomation YL(FALSE);

    szFileName = _T("C:/EELPHRE/Legazzate/ClassificaP");

	limit = 16;
	XL.OpenExcelFile(szFileName);
	for(Row=4; Row<4+limit; Row++)
	{
		szValue = XL.GetCellValue(1, Row);
		szValue.CopyChars((wchar_t*)(SP_Squadre[Row-4].Squadra),szValue.GetLength(), szValue, szValue.GetLength());
		szValue = XL.GetCellValue(3, Row);
		conv2float( &(SP_Squadre[Row-4].voto), szValue);
	}

	Presidente_goals();

	for(Row=0; Row<(limit-1); Row++)
		for(i=Row+1; i<limit; i++)
		{
			if(SP_Squadre[i].voto > SP_Squadre[Row].voto)
			{
				memcpy(Aux.Squadra, SP_Squadre[Row].Squadra, 16*sizeof(TCHAR));
				Aux.voto = SP_Squadre[Row].voto;
				memcpy(SP_Squadre[Row].Squadra, SP_Squadre[i].Squadra, 16*sizeof(TCHAR));
				SP_Squadre[Row].voto = SP_Squadre[i].voto;
				memcpy(SP_Squadre[i].Squadra, Aux.Squadra, 16*sizeof(TCHAR));
				SP_Squadre[i].voto = Aux.voto;
			}
		}
	for(Row=4; Row<4+limit; Row++)
	{
		XL.SetCellValue(1, Row, SP_Squadre[Row-4].Squadra);
		szValue.Format(L"%f", SP_Squadre[Row-4].voto);
		XL.SetCellValue(3, Row, szValue);
	}
	XL.SaveFileAs(szFileName);
	XL.ReleaseExcel();
}

void QuantoSeiPippa::OnBnClickedMostragiornata()
{
	int i;
	CString StrText;
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.

	FinestraListaSquadre.ResetContent();
	//Riporta giornata
    for(i=0; i<5; i++)
	{
		StrText.Format(L"%-17s %-17s\n", A_day[i][0].NomeSquadra, A_day[i][1].NomeSquadra);
		FinestraListaSquadre.AddString(StrText);
		StrText.Format(L"%-17.1f %-3.1f\n", A_day[i][0].voto_finale, A_day[i][1].voto_finale);
		FinestraListaSquadre.AddString(StrText);
	}
	StrText.Format(L"\n");
	FinestraListaSquadre.AddString(StrText);
    for(i=0; i<3; i++)
	{
      StrText.Format(L"%-17s %-17s\n", B_day[i][0].NomeSquadra, B_day[i][1].NomeSquadra);
	  FinestraListaSquadre.AddString(StrText);
      StrText.Format(L"%-17.1f %-3.1f\n", B_day[i][0].voto_finale, B_day[i][1].voto_finale);
	  FinestraListaSquadre.AddString(StrText);
	}
	// popola le editbox dei selettori
    for(i=0;i<10;i++)
	{
      StrText.Format(L"%s", SquadreA[i].NickName);
	  SetDlgItemText(idc_edit_sqr[i], StrText);
	}
	for(i=0;i<6;i++)
    {
		StrText.Format(L"%s", SquadreB[i].NickName);
		SetDlgItemText(idc_edit_sqr[10+i], StrText);
    }
}

void QuantoSeiPippa::OnBnClickedMostraSpc()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
	    //mostra pop-up
	ClassificaP_Dialog.DoModal();
}
