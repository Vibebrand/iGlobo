Ext.regModel('TituloBajoNivelesSNI',{
	fields : ['nombreTitulo', 'C', 'I', 'II', 'III']
});

 Ext.regStore({                                                         //4
       model   : 'TituloBajoNivelesSNI',
       storeId : 'TitulosBajoNivelesStore',
       data :  [            {
								'nombreTitulo': 'Diplomado',
								'C': 0,
                                'I': 0,
								'II': 0,
								'II' : 0
							},
							{
								'nombreTitulo': 'Doctorado',
								'C': 0,
                                'I': 0,
								'II': 0,
								'III' : 0
							},
							{
								'nombreTitulo': 'Especialidad',
								'C': 0,
                                'I': 0,
								'II': 0,
								'III' : 0
							},
                            {
                            	'nombreTitulo': 'Licenciatura',
                            	'C': 0,
                                'I': 0,
                            	'II': 0,
                            	'III' : 0
							},
                            {
                                'nombreTitulo': 'Maestria',
                                'C': 0,
                                'I': 0,
                                'II': 0,
                                'III' : 0
                            },
                            {
                                'nombreTitulo': 'Posdoctorado',
                                'C': 0,
                                'I': 0,
                                'II': 0,
                                'III' : 0
                            }]
   });