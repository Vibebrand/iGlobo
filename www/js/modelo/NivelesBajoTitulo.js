Ext.regModel('NivelesSNIBajoTiTulos',{
	fields : ['nombreNivel', 'Diplomado', 'Doctorado', 'Especialidad', 'Licenciatura', 'Maestria', 'Posdoctorado']
});

 Ext.regStore({                                                         
       model   : 'NivelesSNIBajoTiTulos',
       storeId : 'NivelesSNIBajoTiTulosStore',
       data :  [
                            {
                                'nombreNivel': 'C',
                                'Diplomado': 3,
                                'Doctorado': 19,
                                'Especialidad': 7,
                                'Licenciatura': 8,
                                'Maestria': 1,
                                'Posdoctorado' : 2
                            },
                            {
								'nombreNivel': 'I',
								'Diplomado': 2,
								'Doctorado': 35,
								'Especialidad': 7,
                                'Licenciatura': 0,
                                'Maestria': 0,
                                'Posdoctorado' : 2
							},
							{
								'nombreNivel': 'II',
                                'Diplomado': 0,
                                'Doctorado': 9,
                                'Especialidad': 1,
                                'Licenciatura': 1,
                                'Maestria': 0,
                                'Posdoctorado' : 0
							},
							{
								'nombreNivel': 'III',
                                'Diplomado': 0,
                                'Doctorado': 1,
                                'Especialidad': 0,
                                'Licenciatura': 0,
                                'Maestria': 0,
                                'Posdoctorado' : 0
							}]
   });